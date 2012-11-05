/* Copyright 2010, 2011 Thomas McGuire <mcguire@kde.org>

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

#include "util.h"

#include <KDebug>

using namespace KFbAPI;

static const int invalidTimezone = 42;

class UserInfo::UserInfoPrivate : public QSharedData {
public:
    QString id;
    QString name;
    QString firstName;
    QString lastName;
    QDate birthday;
    QUrl website;
    QString username;
    QString country;
    QString city;
    QString company;
    QString profession;
    QString partner;
    QString updatedTime;
    int timezone;
    QUrl pictureUrl;
};

UserInfo::UserInfo()
    : d(new UserInfoPrivate)
{
    d->timezone = invalidTimezone;
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
    return d->name;
}

QString UserInfo::id() const
{
    return d->id;
}

void UserInfo::setName(const QString &name)
{
    d->name = name;
}

void UserInfo::setId(const QString &id)
{
    d->id = id;
}

QDate UserInfo::birthday() const
{
    return d->birthday;
}

QString UserInfo::birthdayString() const
{
    return d->birthday.toString();
}

QString UserInfo::firstName() const
{
    return d->firstName;
}

QString UserInfo::lastName() const
{
    return d->lastName;
}

void UserInfo::setBirthday(const QString &birthday)
{
    d->birthday = QDate::fromString(birthday, "MM/dd/yyyy");
    if (!d->birthday.isValid()) {
        // Some users don't tell the year of their birthday.
        d->birthday = QDate::fromString(birthday + "/0001", "MM/dd/yyyy");
    }
}

void UserInfo::setFirstName(const QString &firstName)
{
    d->firstName = firstName;
}

void UserInfo::setLastName(const QString &lastName)
{
    d->lastName = lastName;
}

QUrl UserInfo::website() const
{
    return d->website;
}

void UserInfo::setWebsite(const QUrl &website)
{
    if (website.toString().contains('\r') || website.toString().contains('\n')) {
        QString normalized = website.toString();
        normalized.replace("\r\n", "\n");
        normalized.replace("\r", "\n");
        const QStringList websites = normalized.split('\n');
        d->website = QUrl(websites[0]);
    } else {
        d->website = website;
    }
}

void UserInfo::setCity(const QString &city)
{
    d->city = city;
}

void UserInfo::setCountry(const QString &country)
{
    d->country = country;
}

QString UserInfo::username() const
{
    return d->username;
}

void UserInfo::setUsername(const QString &username)
{
    d->username = username;
}

QString UserInfo::company() const
{
    return d->company;
}

QString UserInfo::profession() const
{
    return d->profession;
}

void UserInfo::setCompany(const QString &company)
{
    d->company = company;
}

void UserInfo::setProfession(const QString &profession)
{
    d->profession = profession;
}

QString UserInfo::partner() const
{
    return d->partner;
}

void UserInfo::setPartner(const QString &partner)
{
    d->partner = partner;
}

void UserInfo::setTimezone(int timezone)
{
    d->timezone = timezone;
}

int UserInfo::timezone() const
{
    return d->timezone;
}

KABC::Addressee UserInfo::toAddressee() const
{
    KABC::Addressee addressee;
    addressee.setGivenName(firstName());
    addressee.setUid(id());
    addressee.setFamilyName(lastName());
    addressee.setFormattedName(name());
    addressee.setUrl(website());
    addressee.setBirthday(QDateTime(birthday()));
    addressee.setOrganization(d->company);
    if (d->timezone != invalidTimezone) {
        addressee.setTimeZone(KABC::TimeZone(d->timezone));
    }
    addressee.insertCustom("KADDRESSBOOK", "X-Profession", d->profession);
    addressee.insertCustom("KADDRESSBOOK", "X-SpousesName", d->partner);
    if (!d->city.isEmpty() || !d->country.isEmpty()) {
        KABC::Address address(KABC::Address::Home);
        address.setRegion(d->country);
        address.setLocality(d->city);
        addressee.insertAddress(address);
    }
    return addressee;
}

void UserInfo::setUpdatedTimeString(const QString &updatedTime)
{
    d->updatedTime = updatedTime;
}

QString UserInfo::updatedTimeString() const
{
    return d->updatedTime;
}

KDateTime UserInfo::updatedTime() const
{
    return facebookTimeToKDateTime(d->updatedTime);
}

void UserInfo::setPicture(const QUrl &pictureUrl)
{
    d->pictureUrl = pictureUrl;
}

QUrl UserInfo::picture() const
{
    return d->pictureUrl;
}
