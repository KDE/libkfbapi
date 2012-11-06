/* Copyright 2012 Martin Klapetek <mklapetek@kde.org>

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

#ifndef KFBAPI_NOTIFICATIONINFOPARSER_H
#define KFBAPI_NOTIFICATIONINFOPARSER_H

#include "notificationinfo.h"

#include <QObject>

namespace KFbAPI {

class NotificationInfoParser : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString id WRITE setId READ id)
    Q_PROPERTY(QVariantMap from WRITE setFrom READ fromMap)
    Q_PROPERTY(QVariantMap to WRITE setTo READ toMap)
    Q_PROPERTY(QString created_time WRITE setCreatedTimeString READ createdTimeString)
    Q_PROPERTY(QString updated_time WRITE setUpdatedTimeString READ updatedTimeString)
    Q_PROPERTY(QString title WRITE setTitle READ title)
    Q_PROPERTY(QString message WRITE setMessage READ message)
    Q_PROPERTY(QUrl link WRITE setLink READ link)
    Q_PROPERTY(QVariantMap application WRITE setApplication READ applicationMap)
    Q_PROPERTY(bool unread WRITE setUnread READ unread)

public:
    void setDataObject(const NotificationInfo &notificationInfo) {m_notificationInfo = notificationInfo;}
    NotificationInfo dataObject() const {return m_notificationInfo;}

    void setId(const QString &id) {m_notificationInfo.setId(id);}
    QString id() const {return m_notificationInfo.id();}

    void setFrom(const QVariantMap &from) {m_notificationInfo.setFrom(from);}
    QVariantMap fromMap() const {return m_notificationInfo.fromMap();}

    void setTo(const QVariantMap &to) {m_notificationInfo.setTo(to);}
    QVariantMap toMap() const {return m_notificationInfo.toMap();}

    void setCreatedTimeString(const QString &createdTimeString) {m_notificationInfo.setCreatedTimeString(createdTimeString);}
    QString createdTimeString() const {return m_notificationInfo.createdTimeString();}

    void setUpdatedTimeString(const QString &updatedTimeString) {m_notificationInfo.setUpdatedTimeString(updatedTimeString);}
    QString updatedTimeString() const {return m_notificationInfo.updatedTimeString();}

    void setTitle(const QString &title) {m_notificationInfo.setTitle(title);}
    QString title() const {return m_notificationInfo.title();}

    void setMessage(const QString &message) {m_notificationInfo.setMessage(message);}
    QString message() const {return m_notificationInfo.message();}

    void setLink(const QUrl &link) {m_notificationInfo.setLink(link);}
    QUrl link() const {return m_notificationInfo.link();}

    void setApplication(const QVariantMap &application) {m_notificationInfo.setApplication(application);}
    QVariantMap applicationMap() const {return m_notificationInfo.applicationMap();}

    void setUnread(bool unread) {m_notificationInfo.setUnread(unread);}
    bool unread() const {return m_notificationInfo.unread();}

private:
    NotificationInfo m_notificationInfo;
};

}

#endif
