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

#ifndef KFBAPI_FACEBOOKJOBS_H
#define KFBAPI_FACEBOOKJOBS_H

#include "libkfbapi_export.h"

#include <KJob>
#include <KUrl>

#include <QStringList>
#include <QPointer>

namespace KFbAPI {

class FacebookJobPrivate;
class FacebookGetJobPrivate;

/**
 * FacebookJob base class
 */
class LIBKFBAPI_EXPORT FacebookJob : public KJob
{
    Q_OBJECT
public:
    /**
     * Constructor that sets the path and the accesstoken
     *
     * @param path The path after https://graphs.facebook.com
     * @param accessToken The accessToken to access our data on facebook
     * */
    FacebookJob(const QString &path, const QString &accessToken, QObject *parent = 0);

    /** Add a query item to the list */
    void addQueryItem(const QString &key, const QString &value);

    enum JobErrorType { AuthenticationProblem = KJob::UserDefinedError + 42 };

protected:
    /** Kill the currentjobs and its subjobs */
    virtual bool doKill();

    /** Check for a return error and set the appropiate error messags */
    void handleError(const QVariant &data);

    FacebookJob(FacebookJobPrivate &dd, const QString &path, const QString &accessToken, QObject *parent = 0);

    FacebookJobPrivate * const d_ptr;

private Q_SLOTS:
    virtual void jobFinished(KJob *job) = 0;

private:
    Q_DECLARE_PRIVATE(FacebookJob);
};

/**
 * FacebookJob that adds data to facebook
 */
class LIBKFBAPI_EXPORT FacebookAddJob : public FacebookJob
{
    Q_OBJECT

public:
    FacebookAddJob(const QString &path, const QString &accessToken, QObject *parent = 0);

    virtual void start();

private Q_SLOTS:
    void jobFinished(KJob *job);
};

/**
 * FacebookJob that deletes data from facebook
 */
class LIBKFBAPI_EXPORT FacebookDeleteJob : public FacebookJob
{
    Q_OBJECT

public:
    FacebookDeleteJob(const QString &id, const QString &accessToken, QObject *parent = 0);

    virtual void start();

private Q_SLOTS:
    void jobFinished(KJob *job);
};

/**
 * FacebookJob that gets data from facebook
 */
class LIBKFBAPI_EXPORT FacebookGetJob : public FacebookJob
{
    Q_OBJECT

public:
    FacebookGetJob(const QString &path, const QString &accessToken, QObject *parent = 0);

    /** Set the fields the job should retrieve from facebook */
    void setFields(const QStringList &fields);

    /** Set the Id's the job should retrieve from facebook.
     * If this is set then the path is ignored */
    void setIds(const QStringList &ids);

    virtual void start();

protected:
    virtual void handleData(const QVariant &data) = 0;

    FacebookGetJob(FacebookGetJobPrivate &dd, const QString &path, const QString &accessToken, QObject *parent = 0);

protected Q_SLOTS:
    void jobFinished(KJob *job);

private:
    Q_DECLARE_PRIVATE(FacebookGetJob);

};

/**
 * A FacebookGetJob to retrieve a single or multiple elements from facebook
 * based on their facebook id.
 */
class LIBKFBAPI_EXPORT FacebookGetIdJob : public FacebookGetJob
{
    Q_OBJECT
public:
    /**
     * @brief Constructor to retrieve a list of ids from facebook.
     *
     * @param ids A list of ids to retrieve from facebook.
     * @param accessToken The access token to retrieve data from facebook.
     */
    FacebookGetIdJob(const QStringList &ids, const QString &accessToken, QObject *parent = 0);

    /**
     * @brief Constructor to retrieve a single item from facebook.
     *
     * @param id The id of the item to retrieve from facebook.
     * @param accessToken The access token to retrieve the data from facebook.
     */
    FacebookGetIdJob(const QString &id, const QString &accessToken, QObject *parent = 0);

protected:
    /**
     * @brief Parse a single item that is returned by the FacebookGetJob and
     *        add it to the interl list of elements.
     */
    virtual void handleSingleData(const QVariant &data) = 0;

    //FacebookGetIdJob(FacebookGetJobPrivate &dd, const QString &path, const QString &accessToken, QObject *parent = 0);

private:
    virtual void handleData(const QVariant &data);

//     FacebookGetIdJobPrivate * const d_ptr;
    Q_DECLARE_PRIVATE(FacebookGetJob);
};

}

#endif
