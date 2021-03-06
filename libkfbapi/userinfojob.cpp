/* Copyright 2010 Thomas McGuire <mcguire@kde.org>

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
#include "userinfoparser_p.h"
#include "facebookjobs_p.h"

#include <qjson/qobjecthelper.h>

using namespace KFbAPI;

class KFbAPI::UserInfoJobPrivate : public KFbAPI::FacebookGetJobPrivate {
public:
    UserInfo userInfo;
};

//-----------------------------------------------------------------------------

UserInfoJob::UserInfoJob(const QString &accessToken, QObject *parent)
    : FacebookGetJob(*new UserInfoJobPrivate, "/me", accessToken, parent)
{
    setFields(QStringList() << "name");
}

UserInfoJob::UserInfoJob(const QString &userId, const QString &accessToken, QObject *parent)
    : FacebookGetJob(*new UserInfoJobPrivate, "/" + userId, accessToken, parent)
{
}

UserInfo UserInfoJob::userInfo() const
{
    Q_D(const UserInfoJob);
    return d->userInfo;
}

void UserInfoJob::handleData(const QVariant &data)
{
    Q_D(UserInfoJob);
    UserInfoParser parser;

    QJson::QObjectHelper::qvariant2qobject(data.toMap(), &parser);
    d->userInfo = parser.dataObject();
}

#include "userinfojob.moc"
