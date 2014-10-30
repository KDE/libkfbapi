/* Copyright 2010 Thomas McGuire <mcguire@kde.org>
   Copyright (c) 2014 Martin Klapetek <mklapetek@kde.org>

   This library is free software; you can redistribute it and/or modify
   it under the terms of the GNU Library General Public License as published
   by the Free Software Foundation; either version 2 of the License or
   ( at your option ) version 3 or, at the discretion of KDE e.V.
   ( which shall act as a proxy as in section 14 of the GPLv3 ), any later version.

   This library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Library General Public License for more details.

   You should have received a copy of the GNU Library General Public License
   along with this library; see the file COPYING.LIB.  If not, write to
   the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.
*/

#include "userinfojob.h"
#include "userinfo.h"
#include "facebookjobs_p.h"

#include <QDebug>
#include <QJsonObject>

using namespace KFbAPI;

class KFbAPI::UserInfoJobPrivate : public KFbAPI::FacebookGetJobPrivate {
public:
    UserInfo userInfo;
};

//-----------------------------------------------------------------------------

UserInfoJob::UserInfoJob(const QString &accessToken, QObject *parent)
    : FacebookGetJob(*new UserInfoJobPrivate, QStringLiteral("/me"), accessToken, parent)
{
    // this is querying /me, ie. the user that is logged in
    setFields(QStringList() << QStringLiteral("id")
                            << QStringLiteral("name")
                            << QStringLiteral("first_name")
                            << QStringLiteral("last_name")
                            << QStringLiteral("birthday")
                            << QStringLiteral("website")
                            << QStringLiteral("timezone")
                            << QStringLiteral("updated_time")
                            << QStringLiteral("location"));
}

UserInfoJob::UserInfoJob(const QString &userId, const QString &accessToken, QObject *parent)
    : FacebookGetJob(*new UserInfoJobPrivate, QStringLiteral("/") + userId, accessToken, parent)
{
    // this is querying the user with the given userId
    setFields(QStringList() << QStringLiteral("id")
                            << QStringLiteral("name")
                            << QStringLiteral("first_name")
                            << QStringLiteral("last_name")
                            << QStringLiteral("birthday")
                            << QStringLiteral("website")
                            << QStringLiteral("timezone")
                            << QStringLiteral("updated_time")
                            << QStringLiteral("location"));
}

UserInfo UserInfoJob::userInfo() const
{
    Q_D(const UserInfoJob);
    return d->userInfo;
}

void UserInfoJob::handleData(const QJsonDocument &data)
{
    Q_D(UserInfoJob);

    if (data.isEmpty() || data.isNull()) {
        qWarning() << "Received invalid data";
    }

    d->userInfo = UserInfo(data.object());
}
