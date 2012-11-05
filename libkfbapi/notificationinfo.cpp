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
#include "userinfoparser_p.h"
#include "appinfoparser_p.h"

using namespace KFbAPI;

class NotificationInfo::NotificationInfoPrivate : public QSharedData {
public:
    QString id;          /* Facebook notification id */
    UserInfo from;       /* User from whom the notification originates */
    UserInfo to;         /* User receiving the notification */
    QString createdTime; /* Creation time of the post. */
    QString updatedTime; /* Last update time of the post. */
    QString title;       /* Title of the notification */
    QUrl link;           /* Link for the notification */
    AppInfo app;         /* App causing the notification */
    bool unread;         /* Status of the notification, true if unread, false otherwise */
};

NotificationInfo::NotificationInfo()
    : d(new NotificationInfoPrivate)
{
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

void NotificationInfo::setId(const QString &id)
{
    d->id = id;
}

QString NotificationInfo::id() const
{
    return d->id;
}

void NotificationInfo::setFrom(const QVariantMap &from)
{
    UserInfoParser parser;
    QJson::QObjectHelper::qvariant2qobject(from, &parser);
    d->from = parser.dataObject();
}

UserInfo NotificationInfo::from() const
{
    return d->from;
}

QVariantMap NotificationInfo::fromMap() const
{
    UserInfoParser parser;
    parser.setDataObject(d->from);
    return QJson::QObjectHelper::qobject2qvariant(&parser);
}

void NotificationInfo::setTo(const QVariantMap &to)
{
    UserInfoParser parser;
    QJson::QObjectHelper::qvariant2qobject(to, &parser);
    d->to = parser.dataObject();
}

UserInfo NotificationInfo::to() const
{
    return d->to;
}

QVariantMap NotificationInfo::toMap() const
{
    UserInfoParser parser;
    parser.setDataObject(d->to);
    return QJson::QObjectHelper::qobject2qvariant(&parser);
}

void NotificationInfo::setCreatedTimeString(const QString &time)
{
    d->createdTime = time;
}

QString NotificationInfo::createdTimeString() const
{
    return d->createdTime;
}

KDateTime NotificationInfo::createdTime() const
{
    return facebookTimeToKDateTime(d->createdTime);
}

void NotificationInfo::setUpdatedTimeString(const QString &time)
{
    d->updatedTime = time;
}

QString NotificationInfo::updatedTimeString() const
{
    return d->updatedTime;
}

KDateTime NotificationInfo::updatedTime() const
{
    return facebookTimeToKDateTime(d->updatedTime);
}

void NotificationInfo::setTitle(const QString &title)
{
    d->title = title;
}

QString NotificationInfo::title() const
{
    return d->title;
}

void NotificationInfo::setLink(const QUrl &link)
{
    d->link = link;
}

QUrl NotificationInfo::link() const
{
    return d->link;
}

void NotificationInfo::setApplication(const QVariantMap &app)
{
    AppInfoParser parser;
    QJson::QObjectHelper::qvariant2qobject(app, &parser);
    d->app = parser.dataObject();
}

AppInfo NotificationInfo::application() const
{
    return d->app;
}

QVariantMap NotificationInfo::applicationMap() const
{
    AppInfoParser parser;
    parser.setDataObject(d->app);
    return QJson::QObjectHelper::qobject2qvariant(&parser);
}

void NotificationInfo::setUnread(bool unread)
{
    d->unread = unread;
}

bool NotificationInfo::unread() const
{
    return d->unread;
}
