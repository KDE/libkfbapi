/* Copyright 2010 Thomas McGuire <mcguire@kde.org>

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

#include "friendlistjob.h"
#include "userinfoparser_p.h"

#include <qjson/qobjecthelper.h>

using namespace KFbAPI;

class KFbAPI::FriendListJobPrivate {
public:
    QList<UserInfo> friends;
};

//-----------------------------------------------------------------------------

FriendListJob::FriendListJob(const QString &accessToken, QObject *parent)
    : FacebookGetJob("/me/friends", accessToken, parent),
      d_ptr(new FriendListJobPrivate)
{
}

FriendListJob::~FriendListJob()
{
    delete d_ptr;
}

QList<UserInfo> FriendListJob::friends() const
{
    Q_D(const FriendListJob);
    return d->friends;
}

void FriendListJob::handleData(const QVariant &root)
{
    Q_D(FriendListJob);
    UserInfoParser parser;
    const QVariant data = root.toMap()["data"];
    foreach (const QVariant &user, data.toList()) {
        parser.setDataObject(UserInfo());
        QJson::QObjectHelper::qvariant2qobject(user.toMap(), &parser);
        d->friends.append(parser.dataObject());
    }
}

#include "friendlistjob.moc"
