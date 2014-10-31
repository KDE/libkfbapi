/* Copyright 2010, 2011 Thomas McGuire <mcguire@kde.org>
   Copyright (c) 2014 Martin Klapetek <mklapetek@kde.org>

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
#include "userinfo.h"

#include <QUrl>

using namespace KFbAPI;

class UserInfo::UserInfoPrivate : public QSharedData {
public:
    QJsonObject jsonData;
};

UserInfo::UserInfo()
    : d(new UserInfoPrivate)
{

}

UserInfo::UserInfo(const QJsonObject &jsonData)
    : d(new UserInfoPrivate)
{
    d->jsonData = jsonData;
}


UserInfo::UserInfo(const UserInfo &other)
{
    d = other.d;
}

UserInfo::~UserInfo()
{
    //delete d;
}

UserInfo& UserInfo::operator=(const UserInfo &other)
{
    if (this == &other) return *this; //Protect against self-assignment
    d = other.d;
    return *this;
}

QString UserInfo::name() const
{
    return d->jsonData.value(QStringLiteral("name")).toString();
}

QString UserInfo::id() const
{
    return d->jsonData.value(QStringLiteral("id")).toString();
}

QDate UserInfo::birthday() const
{
    QString dateString = d->jsonData.value(QStringLiteral("birthday")).toString();

    if (dateString.count(QLatin1Char('/')) == 2) {
        // the date contains a year too
        return QDate::fromString(dateString, QStringLiteral("MM/dd/yyyy"));
    } else if (dateString.count(QLatin1Char('/')) == 1) {
        // the date has only month/day
        return QDate::fromString(dateString, QStringLiteral("MM/dd"));
    }

    return QDate();
}

QString UserInfo::birthdayString() const
{
    return d->jsonData.value(QStringLiteral("birthday")).toString();
}

QString UserInfo::firstName() const
{
    return d->jsonData.value(QStringLiteral("first_name")).toString();
}

QString UserInfo::lastName() const
{
    return d->jsonData.value(QStringLiteral("last_name")).toString();
}

QUrl UserInfo::website() const
{
    return QUrl::fromUserInput(d->jsonData.value(QStringLiteral("website")).toString());
}

QString UserInfo::username() const
{
    return d->jsonData.value(QStringLiteral("username")).toString();
}

// QString UserInfo::company() const
// {
//     return d->jsonData.value(QStringLiteral("")).toString();
// }
//
// QString UserInfo::profession() const
// {
//     return d->profession;
// }

QString UserInfo::partner() const
{
    return d->jsonData.value(QStringLiteral("partner")).toString();
}

int UserInfo::timezone() const
{
    return d->jsonData.value(QStringLiteral("timezone")).toInt();
}

// KABC::Addressee UserInfo::toAddressee() const
// {
//     KABC::Addressee addressee;
//     addressee.setGivenName(firstName());
//     addressee.setUid(id());
//     addressee.setFamilyName(lastName());
//     addressee.setFormattedName(name());
//     addressee.setUrl(website());
//     addressee.setBirthday(QDateTime(birthday()));
//     addressee.setOrganization(d->company);
//     if (d->timezone != invalidTimezone) {
//         addressee.setTimeZone(KABC::TimeZone(d->timezone));
//     }
//     addressee.insertCustom("KADDRESSBOOK", "X-Profession", d->profession);
//     addressee.insertCustom("KADDRESSBOOK", "X-SpousesName", d->partner);
//     if (!d->city.isEmpty() || !d->country.isEmpty()) {
//         KABC::Address address(KABC::Address::Home);
//         address.setRegion(d->country);
//         address.setLocality(d->city);
//         addressee.insertAddress(address);
//     }
//     return addressee;
// }

QString UserInfo::updatedTimeString() const
{
    return d->jsonData.value(QStringLiteral("updated_time")).toString();
}

QDateTime UserInfo::updatedTime() const
{
    return QDateTime::fromString(d->jsonData.value(QStringLiteral("updated_time")).toString(), Qt::ISODate);
}

QUrl UserInfo::picture() const
{
    QJsonObject pictureObject = d->jsonData.value(QStringLiteral("picture")).toObject();
    if (pictureObject.value(QStringLiteral("is_silhouette")).toBool() == true) {
        //TODO: return our custom silhouette icon here
        return QUrl::fromUserInput(pictureObject.value(QStringLiteral("url")).toString());
    } else {
        return QUrl::fromUserInput(pictureObject.value(QStringLiteral("url")).toString());
    }
}
