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

#include <qjson/qobjecthelper.h>

#include <KDateTime>

namespace KFbAPI {

/**
 * Class to represent a facebook notification.
 * See https://developers.facebook.com/docs/reference/api/user/#notifications
 */

class LIBKFBAPI_EXPORT NotificationInfo
{
public:
    NotificationInfo();
    NotificationInfo(const NotificationInfo &other);
    ~NotificationInfo();

    NotificationInfo &operator=(const NotificationInfo &other);

    /**
     * Set the notification id of the post
     * @param id of the notification
     */
    void setId(const QString &id);
    /**
     * Returns notification id
     */
    QString id() const;

    /**
     * Set the user creating the notification
     * @param from the user causing the notification
     */
    void setFrom(const QVariantMap &from);
    /**
     * Returns the user causing the notification as a User Info Object
     */
    UserInfo from() const;

    /**
     * Returns the user causing the notification as a QVariantMap
     */
    QVariantMap fromMap() const;

    /**
     * Set the user receiving the notification
     * @param to the user receiving the notification
     */
    void setTo(const QVariantMap &to);
    /**
     * Returns the user receiving the notification as a User Info Object
     */
    UserInfo to() const;

    /**
     * Returns the user receiving the notification as a QVariantMap
     */
    QVariantMap toMap() const;

    /**
     * Set the creation time of the notification
     * @param createdTime Time in "facebook format"
     */
    void setCreatedTimeString(const QString &time);
    /**
     * Returns the creation time as a string in "facebook format"
     */
    QString createdTimeString() const;
    /**
     * Returns the creation time in KDateTime
     */
    KDateTime createdTime() const;

    /**
     * Set the time of the last update of the notification
     * @param updatedTime The time, in "facebook format", of the last update of
     *                    the notification.
     */
    void setUpdatedTimeString(const QString &time);
    /**
     * Returns the time of the last update of the notification in "facebook format"
     */
    QString updatedTimeString() const;
    /**
     * Returns the time of the last update of the notification as a KDateTime
     */
    KDateTime updatedTime() const;


    /**
     * Set the title of the notification (it's the notification text itself)
     * @param title Title of the notification
     */
    void setTitle(const QString &title);
    /**
     * Returns notification title (which is the notification text itself)
     */
    QString title() const;

    /**
     * Set the link for the notification
     * @param link Link for the notification
     */
    void setLink(const QString &link);
    /**
     * Returns link for the notification
     */
    QString link() const;

    /**
     * Set application details that caused the notification
     * @param app The app that caused the notification
     */
    void setApplication(const QVariantMap &app);
    /**
     * Returns the creator app that caused the notification
     */
    AppInfo application() const;

    /**
     * Returns the creator app that caused the notification as QVariantMap
     */
    QVariantMap applicationMap() const;

    /**
     * Set the notification as read/unread
     * @param unread True if the notification is read, false otherwise
     */
    void setUnread(bool unread);
    /**
     * Returns whether the user has read the notification or not
     */
    bool unread() const;

private:
    class NotificationInfoPrivate;
    QSharedDataPointer<NotificationInfoPrivate> d;
};

}

Q_DECLARE_METATYPE(KFbAPI::NotificationInfo);

#endif // NOTIFICATIONINFO_H
