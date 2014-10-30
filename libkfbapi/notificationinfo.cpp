/* Copyright 2012 Martin Klapetek <martin.klapetek@gmail.com>

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

#include "notificationinfo.h"
#include "userinfo.h"
#include "appinfo.h"
#include "util.h"

#include <qjson/qobjecthelper.h>

using namespace KFbAPI;

class NotificationInfo::NotificationInfoPrivate : public QSharedData {
public:
    QJsonObject jsonData;
};

NotificationInfo::NotificationInfo()
    : d(new NotificationInfoPrivate)
{
}

NotificationInfo::NotificationInfo(const QJsonObject &jsonData)
    : d(new NotificationInfoPrivate)
{
    d->jsonData = jsonData;
}


NotificationInfo::NotificationInfo(const NotificationInfo &other)
{
    d = other.d;
}

NotificationInfo::~NotificationInfo()
{
}

NotificationInfo& NotificationInfo::operator=(const NotificationInfo &other)
{
    if (this == &other) return *this; //Protect against self-assignment
    d = other.d;
    return *this;
}

QString NotificationInfo::id() const
{
    return d->jsonData.value(QStringLiteral("id")).toString();
}

UserInfo NotificationInfo::from() const
{
    return UserInfo(d->jsonData.value(QStringLiteral("from")).toObject());
}

QVariantMap NotificationInfo::fromMap() const
{
    return d->jsonData.value(QStringLiteral("from")).toVariant().toMap();
}

UserInfo NotificationInfo::to() const
{
    return UserInfo(d->jsonData.value(QStringLiteral("to")).toObject());
}

QVariantMap NotificationInfo::toMap() const
{
    return d->jsonData.value(QStringLiteral("to")).toVariant().toMap();
}

QString NotificationInfo::createdTimeString() const
{
    return d->jsonData.value(QStringLiteral("created_time")).toString();
}

QDateTime NotificationInfo::createdTime() const
{
    return QDateTime::fromString(d->jsonData.value(QStringLiteral("created_time")).toString(), Qt::ISODate);
}

QString NotificationInfo::updatedTimeString() const
{
    return d->jsonData.value(QStringLiteral("updated_time")).toString();
}

QDateTime NotificationInfo::updatedTime() const
{
    return QDateTime::fromString(d->jsonData.value(QStringLiteral("updated_time")).toString(), Qt::ISODate);
}

QString NotificationInfo::title() const
{
    return d->jsonData.value(QStringLiteral("title")).toString();
}

QUrl NotificationInfo::link() const
{
    return QUrl::fromUserInput(d->jsonData.value(QStringLiteral("link")).toString());
}

AppInfo NotificationInfo::application() const
{
    return AppInfo(d->jsonData.value(QStringLiteral("application")).toObject());
}

QVariantMap NotificationInfo::applicationMap() const
{
    return d->jsonData.value(QStringLiteral("application")).toVariant().toMap();
}

bool NotificationInfo::unread() const
{
    return d->jsonData.value(QStringLiteral("unread")).toBool();
}
