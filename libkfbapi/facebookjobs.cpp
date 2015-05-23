/* Copyright 2010, 2011 Thomas McGuire <mcguire@kde.org>
   Copyright 2011 Roeland Jago Douma <unix@rullzer.com>
   Copyright 2012 Martin Klapetek <mklapetek@kde.org>

   This library is free software; you can redistribute it and/or modify
   it under the terms of the GNU Library General Public License as published
   by the Free Software Foundation; either version 2 of the License or
   (at your option) version 3 or, at the discretion of KDE e.V.
   (which shall act as a proxy as in section 14 of the GPLv3), any later version.

   This library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Library General Public License for more details.

   You should have received a copy of the GNU Library General Public License
   along with this library; see the file COPYING.LIB.  If not, write to
   the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.
*/

#include "facebookjobs.h"
#include "facebookjobs_p.h"


#include <KJob>
#include <KLocalizedString>
#include <KIO/StoredTransferJob>
#include <KIO/Job> //for KIO::buildErrorString

#include <QUrl>
#include <QDebug>
#include <qjsondocument.h>

// static const KCatalogLoader loader(QStringLiteral("libkfbapi"));

namespace KFbAPI {

/*
 * FacebookJobs base class
 */
FacebookJob::FacebookJob(const QString &path, const QString &accessToken, QObject *parent)
    : KJob(parent),
      d_ptr(new FacebookJobPrivate)
{
    Q_D(FacebookJob);
    d->init(path, accessToken);
    setCapabilities(KJob::Killable);
}

FacebookJob::FacebookJob(FacebookJobPrivate& dd, const QString &path, const QString &accessToken, QObject *parent)
    : KJob(parent),
      d_ptr(&dd)
{
    Q_D(FacebookJob);
    d->init(path, accessToken);
    setCapabilities(KJob::Killable);
}

FacebookJob::~FacebookJob()
{
    delete d_ptr;
}

void FacebookJob::addQueryItem(const QString &key, const QString &value)
{
    Q_D(FacebookJob);
    QUrlQuery query(d->url);
    query.addQueryItem(key, value);
    d->url.setQuery(query);
}

bool FacebookJob::doKill()
{
    Q_D(FacebookJob);
    if (d->job) {
        d->job->kill(KJob::Quietly);
    }

    return KJob::doKill();
}

void FacebookJob::handleError(const QVariant &data)
{
    const QVariantMap errorMap = data.toMap();
    const QString type = errorMap[QStringLiteral("type")].toString();
    const QString message = errorMap[QStringLiteral("message")].toString();

    qWarning() << "An error of type" << type << "occurred:" << message;

    if (type.toLower() != QLatin1String("oauthexception")) {
        setError(KJob::UserDefinedError);
        setErrorText(i18n("The Facebook server returned an error of type <i>%1</i>: <i>%2</i>" , type, message));
    } else {
        setError(AuthenticationProblem);
        setErrorText(i18n("Unable to login to the Facebook server, authentication failure.\nThe server said: <i>%1</i>", message));
    }
}

/*
 * Facebook Add Job
 */
FacebookAddJob::FacebookAddJob(const QString &path, const QString &accessToken, QObject *parent)
    : FacebookJob(path, accessToken, parent)
{
}

void FacebookAddJob::start()
{
    Q_D(FacebookJob);
    qDebug() << "Starting add: " << d->url;
    KIO::StoredTransferJob * const job = KIO::storedHttpPost(QByteArray(), d->url, KIO::HideProgressInfo);
    d->job = job;
    connect(job, SIGNAL(result(KJob*)), this, SLOT(jobFinished(KJob*)));
    job->start();
}

void FacebookAddJob::jobFinished(KJob *job)
{
    Q_D(FacebookJob);
    KIO::StoredTransferJob *addJob = dynamic_cast<KIO::StoredTransferJob *>(job);
    Q_ASSERT(addJob);
    if (addJob->error()) {
        setError(addJob->error());
        setErrorText(KIO::buildErrorString(error(), addJob->errorText()));
        qWarning() << "Job error: " << addJob->errorString();
    } else {
        QJsonParseError error;
        QJsonDocument response = QJsonDocument::fromJson(addJob->data(), &error);
        const QVariant result = response.toVariant();
        if (error.error == QJsonParseError::NoError) {
            qWarning() << "Unable to parse JSON data: " << addJob->data();
            setError(KJob::UserDefinedError);
            setErrorText(i18n("Unable to parse data returned by the Facebook server: %1", error.errorString()));
        } else {
            const QVariant errorData = result.toMap()[QStringLiteral("error")];
            if (errorData.isValid()) {
                handleError(errorData);
            } else {
                const QVariantMap dataMap = result.toMap();
                if (dataMap.contains(QLatin1String("id"))) {
                    setProperty("id", dataMap[QStringLiteral("id")]);
                }
            }
        }
    }

    emitResult();
    d->job = 0;
}

/*
 * Facebook Delete job
 */
FacebookDeleteJob::FacebookDeleteJob(const QString &id, const QString &accessToken, QObject *parent)
    : FacebookJob(QStringLiteral("/") + id, accessToken, parent)
{
}

void FacebookDeleteJob::start()
{
    Q_D(FacebookJob);
    QUrlQuery query(d->url);
    query.addQueryItem(QStringLiteral("method"), QStringLiteral("delete"));
    d->url.setQuery(query);

    qDebug() << "Starting delete: " << d->url;
    KIO::StoredTransferJob * const job = KIO::storedHttpPost(QByteArray(), d->url, KIO::HideProgressInfo);
    d->job = job;
    connect(job, SIGNAL(result(KJob*)), this, SLOT(jobFinished(KJob*)));
    job->start();
}

void FacebookDeleteJob::jobFinished(KJob *job)
{
    Q_D(FacebookJob);
    KIO::StoredTransferJob *deleteJob = dynamic_cast<KIO::StoredTransferJob *>(job);
    Q_ASSERT(deleteJob);
    if (deleteJob->error()) {
        setError(deleteJob->error());
        setErrorText(KIO::buildErrorString(error(), deleteJob->errorText()));
        qWarning() << "Job error: " << deleteJob->errorString();
    } else {
        // TODO: error handling. Does the server return the error as a JSON string?
    //     qDebug() << "Got data: " << QString::fromAscii(deleteJob->data().data());
    }

    emitResult();
    d->job = 0;
}

/*
 * Facebook get job
 */
FacebookGetJob::FacebookGetJob(const QString &path, const QString &accessToken, QObject *parent)
    : FacebookJob(*new FacebookGetJobPrivate, path, accessToken, parent)
{
    Q_D(FacebookGetJob);
    d->multiQuery = false;
}

FacebookGetJob::FacebookGetJob(FacebookGetJobPrivate &dd, const QString &path, const QString &accessToken, QObject *parent)
    : FacebookJob(dd, path, accessToken, parent)
{
    Q_D(FacebookGetJob);
    d->multiQuery = false;
}

FacebookGetJob::~FacebookGetJob()
{
}

void FacebookGetJob::setIds(const QStringList &ids)
{
    Q_D(FacebookGetJob);
    d->ids = ids;
}

void FacebookGetJob::setFields(const QStringList &fields)
{
    Q_D(FacebookGetJob);
    d->fields = fields;
}

void FacebookGetJob::start()
{
    Q_D(FacebookGetJob);

    //let's keep our d->url intact
    QUrl jobUrl = d->url;
    QUrlQuery query(jobUrl);

    if (!d->ids.isEmpty()) {
        //check if we are requesting more than 15 ids
        if (d->multiQuery && d->ids.size() > 15) {
            qDebug() << "Got multiquery with more than 15 items";
            //if yes, we take the first 15 ids and query for those
            QStringList l;
            for (int i = 0; i < 15 && d->ids.size() > 0; i++) {
                l << d->ids.takeFirst();
            }
            query.addQueryItem(QStringLiteral("ids"), l.join(QStringLiteral(",")));
        } else {
            //we have less than 15 ids
            query.addQueryItem(QStringLiteral("ids"), d->ids.join(QStringLiteral(",")));
            d->ids.clear();
        }
    } else if (d->ids.isEmpty() && d->multiQuery) {
        //if we have no ids to query for, return
        qDebug() << "No more ids to query for, job done";
        emitResult();
        d->job = 0;
        return;
    }

    if (!d->fields.isEmpty()) {
        query.addQueryItem(QStringLiteral("fields"), d->fields.join(QStringLiteral(",")));
    }

    jobUrl.setQuery(query);

    qDebug() << "Starting query" << jobUrl;
    KIO::StoredTransferJob * const job = KIO::storedGet(jobUrl, KIO::Reload, KIO::HideProgressInfo);
    d->job = job;
    connect(job, SIGNAL(result(KJob*)), this, SLOT(jobFinished(KJob*)));
    job->start();
}

void FacebookGetJob::jobFinished(KJob *job)
{
    Q_D(FacebookGetJob);
    KIO::StoredTransferJob *transferJob = dynamic_cast<KIO::StoredTransferJob *>(job);
    Q_ASSERT(transferJob);
    if (transferJob->error()) {
        setError(transferJob->error());
        setErrorText(KIO::buildErrorString(error(), transferJob->errorText()));
        qWarning() << "Job error: " << transferJob->errorString();
    } else {

        QJsonParseError error;
        QJsonDocument response = QJsonDocument::fromJson(transferJob->data(), &error);
        const QVariant data = response.toVariant();

        if (error.error == QJsonParseError::NoError) {
            const QVariant errorData = data.toMap()[QStringLiteral("error")];
            if (errorData.isValid()) {
                handleError(errorData);
            } else {
                handleData(response);
            }
        } else {
            qWarning() << "Unable to parse JSON data: " << error.errorString();
            qDebug() << "Received data:" << transferJob->data();
            setError(KJob::UserDefinedError);
            setErrorText(i18n("Unable to parse data returned by the Facebook server: %1", error.errorString()));
        }
    }

    if (d->multiQuery && !d->ids.isEmpty()) {
        //we have some ids left to query for, restarting the job, this will append the new data
        //to the existing data, then it will be returned altogether
        qDebug() << d->ids.size() << "ids left, restarting job";

        start();
        return;
    }

    emitResult();
    d->job = 0;
}

/*
 * FacebookGetIdJob
 */
FacebookGetIdJob::FacebookGetIdJob(const QStringList &ids, const QString &accessToken, QObject *parent)
    : FacebookGetJob(QStringLiteral("/"), accessToken, parent)
{
    Q_D(FacebookGetJob);
    d->multiQuery = true;
    setIds(ids);
}

FacebookGetIdJob::FacebookGetIdJob(const QString &id, const QString &accessToken, QObject *parent)
    : FacebookGetJob(QStringLiteral("/") + id, accessToken, parent)
{
    Q_D(FacebookGetJob);
    d->multiQuery = false;
}

FacebookGetIdJob::~FacebookGetIdJob()
{
}

FacebookGetIdJob::FacebookGetIdJob(FacebookGetJobPrivate &dd, const QString &id, const QString &accessToken, QObject *parent)
    : FacebookGetJob(dd, QStringLiteral("/") + id, accessToken, parent)
{
    Q_D(FacebookGetJob);
    d->multiQuery = false;
}

FacebookGetIdJob::FacebookGetIdJob(FacebookGetJobPrivate &dd, const QStringList &ids, const QString &accessToken, QObject *parent)
    : FacebookGetJob(dd, QStringLiteral("/"), accessToken, parent)
{
    Q_D(FacebookGetJob);
    d->multiQuery = true;
    setIds(ids);
}

void FacebookGetIdJob::handleData(const QJsonDocument &data)
{
    Q_D(FacebookGetJob);

    if (!d->multiQuery) {
        handleSingleData(data);
    } else {
        //TODO: finish this
        qWarning() << data.toVariant();
//         foreach (const QVariant &item, data.toMap()) {
//             handleSingleData(item);
//         }
    }
}
}
