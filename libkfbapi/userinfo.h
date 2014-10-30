/* Copyright 2010, 2011 Thomas McGuire <mcguire@kde.org>
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

#ifndef KFBAPI_USERINFO_H
#define KFBAPI_USERINFO_H

#include "libkfbapi_export.h"

#include <QDateTime>
#include <QSharedPointer>
#include <QJsonObject>
// #include <QDate>

namespace KFbAPI {

/**
* Class that describes a person on facebook
*/
class LIBKFBAPI_EXPORT UserInfo
{
public:
    UserInfo();
    UserInfo(const QJsonObject &jsonData);
    UserInfo(const UserInfo &other);
    ~UserInfo();

    UserInfo &operator=(const UserInfo &other);

    /**
     * @return The facebook id of this person
     */
    QString id() const;

    /**
     * @return The name this person.
     */
    QString name() const;

    /**
     * @return The first name of this person.
     */
    QString firstName() const;

    /**
     * @return The last name of this person.
     */
    QString lastName() const;

    /**
     * @return The birthday as a QString in "facebook format"
     */
    QString birthdayString() const;

    /**
     * @return The birthday of this person as a QDate.
     */
    QDate birthday() const;

    /**
     * @return The url to the website of this user as a QString.
     */
    QUrl website() const;

    /**
     * @return The username of this user as a QString.
     */
    QString username() const;

    /**
     * @return The current location name of this person (may or may not include country too)
     */
    QString locationName() const;

    /**
     * @return The current location ID for this person
     */
    QString locationId() const;

    /**
     * @return The company this person is working at.
     */
    QString company() const;

    /**
     * @return The profession of this person.
     */
    QString profession() const;

    /**
     * @return The partner of this person.
     */
    QString partner() const;

    /**
     * @return The timezone fo this person.
     */
    int timezone() const;

    /**
     * @return The time of the last update of the profile as a QString
     *         in "facebook format"
     */
    QString updatedTimeString() const;
    /**
     * @return The time of the last update of the profile as a KDateTime
     */
    QDateTime updatedTime() const;

//     /**
//      * @brief Created a KABC::Addressee for all the information we have about
//      *        this person.
//      *
//      * @return A KABC::Addressee of this person.
//      */
//     KABC::Addressee toAddressee() const;

    /**
     * @return The profile picture url
     */
    QUrl picture() const;

private:
    class UserInfoPrivate;
    QSharedDataPointer<UserInfoPrivate> d;
};

}

Q_DECLARE_METATYPE(KFbAPI::UserInfo)

#endif
