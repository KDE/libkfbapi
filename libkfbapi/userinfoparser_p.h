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

#ifndef KFBAPI_USERINFOPARSER_H
#define KFBAPI_USERINFOPARSER_H

#include "userinfo.h"

#include <QObject>

namespace KFbAPI {

class UserInfoParser : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString id WRITE setId READ id)
    Q_PROPERTY(QString name WRITE setName READ name)
    Q_PROPERTY(QString first_name WRITE setFirstName READ firstName)
    Q_PROPERTY(QString last_name WRITE setLastName READ lastName)
    Q_PROPERTY(QString birthday WRITE setBirthday READ birthdayAsString)
    Q_PROPERTY(QString website WRITE setWebsite READ website)
    Q_PROPERTY(QString username WRITE setUsername READ username)
    Q_PROPERTY(int timezone WRITE setTimezone READ timezone)
    Q_PROPERTY(QString updated_time WRITE setUpdatedTimeString READ updatedTimeString)
    Q_PROPERTY(QUrl picture WRITE setPicture READ picture)

public:
    void setDataObject(const UserInfo &userInfo) {m_userInfo = userInfo;}
    UserInfo dataObject() const {return m_userInfo;}

    void setId(const QString &id) {m_userInfo.setId(id);}
    QString id() const {return m_userInfo.id();}

    void setName(const QString &name) {m_userInfo.setName(name);}
    QString name() const {return m_userInfo.name();}

    void setFirstName(const QString &firstName) {m_userInfo.setFirstName(firstName);}
    QString firstName() const {return m_userInfo.firstName();}

    void setLastName(const QString &lastName) {m_userInfo.setLastName(lastName);}
    QString lastName() const {return m_userInfo.lastName();}

    void setBirthday(const QString &birthday) {m_userInfo.setBirthday(birthday);}
    QString birthdayAsString() const {return m_userInfo.birthdayAsString();}

    void setWebsite(const QString &website) {m_userInfo.setWebsite(website);}
    QString website() const {return m_userInfo.website();}

    void setUsername(const QString &username) {m_userInfo.setUsername(username);}
    QString username() const {return m_userInfo.username();}

    void setTimezone(int timezone) {m_userInfo.setTimezone(timezone);}
    int timezone() const {return m_userInfo.timezone();}

    void setUpdatedTimeString(const QString &updatedTimeString) {m_userInfo.setUpdatedTimeString(updatedTimeString);}
    QString updatedTimeString() const {return m_userInfo.updatedTimeString();}

    void setPicture(const QUrl &pictureUrl) {m_userInfo.setPicture(pictureUrl);}
    QUrl picture() const {return m_userInfo.picture();}

private:
    UserInfo m_userInfo;
};

}

#endif
