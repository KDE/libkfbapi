/* Copyright 2010, 2011 Thomas McGuire <mcguire@kde.org>

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

#ifndef KFBAPI_FRIENDJOB_H
#define KFBAPI_FRIENDJOB_H

#include "facebookjobs.h"
#include "userinfo.h"

namespace KFbAPI {

class FriendJobPrivate;

/**
 * A job to retrieve the data about one or multiple friends from facebook.
 */
class LIBKFBAPI_EXPORT FriendJob : public FacebookGetIdJob
{
  Q_OBJECT
public:
    /**
    * @brief Constructor to retrieve multiple friends from facebook.
    *
    * @param friendIds A list of ids of the friends you want to retrieve from facebook.
    * @param accessToken The access token to retrieve the data from facebook.
    */
    FriendJob(const QStringList &friendIds, const QString &accessToken, QObject *parent = 0);

    /**
    * @brief Constructor to retrieve a single friend from facebook.
    *
    * @param friendId The id of the friend you want to retrieve data from.
    * @param accessToken The access token to retrieve the data from facebook.
    */
    FriendJob(const QString &friendId, const QString &accessToken, QObject *parent = 0);

    /**
    * @return A list of pointers to UserInfo objects of all the users (friends)
    *         that have been retrieved by this job.
    */
    QList<UserInfo> friendInfo() const;

private:
    Q_DECLARE_PRIVATE(FriendJob)

    void handleSingleData(const QVariant &data);
};

}

#endif
