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

#ifndef KFBAPI_NOTIFICATIONINFO_H
#define KFBAPI_NOTIFICATIONINFO_H

#include "libkfbapi_export.h"
#include "userinfo.h"
#include "appinfo.h"

#include <QJsonObject>

namespace KFbAPI {

/**
 * Class to represent a facebook notification.
 * See https://developers.facebook.com/docs/reference/api/user/#notifications
 */

class LIBKFBAPI_EXPORT NotificationInfo
{
public:
    NotificationInfo(const QJsonObject &jsonData);
    NotificationInfo();
    NotificationInfo(const NotificationInfo &other);
    ~NotificationInfo();

    NotificationInfo &operator=(const NotificationInfo &other);

    /**
     * Returns notification id
     */
    QString id() const;

    /**
     * Returns the user causing the notification as a User Info Object
     */
    UserInfo from() const;

    /**
     * Returns the user causing the notification as a QVariantMap
     */
    QVariantMap fromMap() const;

    /**
     * Returns the user receiving the notification as a User Info Object
     */
    UserInfo to() const;

    /**
     * Returns the user receiving the notification as a QVariantMap
     */
    QVariantMap toMap() const;

    /**
     * Returns the creation time as a string in "facebook format"
     */
    QString createdTimeString() const;

    /**
     * Returns the creation time in KDateTime
     */
    QDateTime createdTime() const;

    /**
     * Returns the time of the last update of the notification in "facebook format"
     */
    QString updatedTimeString() const;

    /**
     * Returns the time of the last update of the notification as a KDateTime
     */
    QDateTime updatedTime() const;

    /**
     * Returns notification title (which is the notification text itself)
     */
    QString title() const;

    /**
     * Returns notification message (usually a comment posted by the user)
     */
    QString message() const;

    /**
     * Returns link for the notification
     */
    QUrl link() const;

    /**
     * Returns the creator app that caused the notification
     */
    AppInfo application() const;

    /**
     * Returns the creator app that caused the notification as QVariantMap
     */
    QVariantMap applicationMap() const;

    /**
     * Returns whether the user has read the notification or not
     */
    bool unread() const;


private:
    class NotificationInfoPrivate;
    QSharedDataPointer<NotificationInfoPrivate> d;
};

}

Q_DECLARE_METATYPE(KFbAPI::NotificationInfo)

#endif // NOTIFICATIONINFO_H
