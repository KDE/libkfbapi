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

#include <qjson/parser.h>

#include <KIO/Job>
#include <KDebug>
#include <KLocale>

static const KCatalogLoader loader("libkfbapi");

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
    d->url.addQueryItem(key, value);
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
    const QString type = errorMap["type"].toString();
    const QString message = errorMap["message"].toString();

    kWarning() << "An error of type" << type << "occurred:" << message;

    if (type.toLower() != "oauthexception") {
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
    kDebug() << "Starting add: " << d->url;
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
        kWarning() << "Job error: " << addJob->errorString();
    } else {
        QJson::Parser parser;
        bool ok;
        const QVariant result = parser.parse(addJob->data(), &ok);
        if (!ok) {
            kWarning() << "Unable to parse JSON data: " << QString::fromAscii(addJob->data().data());
            setError(KJob::UserDefinedError);
            setErrorText(i18n("Unable to parse data returned by the Facebook server: %1", parser.errorString()));
        } else {
            const QVariant error = result.toMap()["error"];
            if (error.isValid()) {
                handleError(error);
            } else {
                const QVariantMap dataMap = result.toMap();
                if (dataMap.contains("id")) {
                    setProperty("id", dataMap["id"]);
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
    : FacebookJob("/" + id, accessToken, parent)
{
}

void FacebookDeleteJob::start()
{
    Q_D(FacebookJob);
    d->url.addQueryItem("method", "delete");

    kDebug() << "Starting delete: " << d->url;
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
        kWarning() << "Job error: " << deleteJob->errorString();
    } else {
        // TODO: error handling. Does the server return the error as a JSON string?
    //     kDebug() << "Got data: " << QString::fromAscii(deleteJob->data().data());
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
    KUrl jobUrl = d->url;

    if (!d->ids.isEmpty()) {
        //check if we are requesting more than 15 ids
        if (d->multiQuery && d->ids.size() > 15) {
            kDebug() << "Got multiquery with more than 15 items";
            //if yes, we take the first 15 ids and query for those
            QStringList l;
            for (int i = 0; i < 15 && d->ids.size() > 0; i++) {
                l << d->ids.takeFirst();
            }
            jobUrl.addQueryItem("ids", l.join(","));
        } else {
            //we have less than 15 ids
            jobUrl.addQueryItem("ids", d->ids.join(","));
            d->ids.clear();
        }
    } else if (d->ids.isEmpty() && d->multiQuery) {
        //if we have no ids to query for, return
        kDebug() << "No more ids to query for, job done";
        emitResult();
        d->job = 0;
        return;
    }

    if (!d->fields.isEmpty()) {
        jobUrl.addQueryItem("fields", d->fields.join(","));
    }

    kDebug() << "Starting query" << jobUrl;
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
        kWarning() << "Job error: " << transferJob->errorString();
    } else {
//         kDebug() << "Got data: " << QString::fromAscii(transferJob->data().data());
        QJson::Parser parser;
        bool ok;
        const QVariant data = parser.parse(transferJob->data(), &ok);
        if (ok) {
            const QVariant error = data.toMap()["error"];
            if (error.isValid()) {
                handleError(error);
            } else {
                handleData(data);
            }
        } else {
            kWarning() << "Unable to parse JSON data: " << QString::fromAscii(transferJob->data().data());
            setError(KJob::UserDefinedError);
            setErrorText(i18n("Unable to parse data returned by the Facebook server: %1", parser.errorString()));
        }
    }

    if (d->multiQuery && !d->ids.isEmpty()) {
        //we have some ids left to query for, restarting the job, this will append the new data
        //to the existing data, then it will be returned altogether
        kDebug() << d->ids.size() << "ids left, restarting job";

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
    : FacebookGetJob("/", accessToken, parent)
{
    Q_D(FacebookGetJob);
    d->multiQuery = true;
    setIds(ids);
}

FacebookGetIdJob::FacebookGetIdJob(const QString &id, const QString &accessToken, QObject *parent)
    : FacebookGetJob("/" + id, accessToken, parent)
{
    Q_D(FacebookGetJob);
    d->multiQuery = false;
}

FacebookGetIdJob::~FacebookGetIdJob()
{
}

FacebookGetIdJob::FacebookGetIdJob(FacebookGetJobPrivate &dd, const QString &id, const QString &accessToken, QObject *parent)
    : FacebookGetJob(dd, "/" + id, accessToken, parent)
{
    Q_D(FacebookGetJob);
    d->multiQuery = false;
}

FacebookGetIdJob::FacebookGetIdJob(FacebookGetJobPrivate &dd, const QStringList &ids, const QString &accessToken, QObject *parent)
    : FacebookGetJob(dd, "/", accessToken, parent)
{
    Q_D(FacebookGetJob);
    d->multiQuery = true;
    setIds(ids);
}

void FacebookGetIdJob::handleData(const QVariant &data)
{
    Q_D(FacebookGetJob);

    if (!d->multiQuery) {
        handleSingleData(data);
    } else {
        foreach (const QVariant &item, data.toMap()) {
            handleSingleData(item);
        }
    }
}
}

#include "facebookjobs.moc"
