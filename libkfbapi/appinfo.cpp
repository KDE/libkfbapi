/* Copyright 2012 Pankaj Bhambhani <pankajb64@gmail.com>
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

#include "appinfo.h"

using namespace KFbAPI;

class AppInfo::AppInfoPrivate : public QSharedData {
public:
    QJsonObject jsonData;
};

AppInfo::AppInfo()
    : d(new AppInfoPrivate)
{
}

AppInfo::AppInfo(const QJsonObject &jsonData)
    : d(new AppInfoPrivate)
{
    d->jsonData = jsonData;
}

AppInfo::AppInfo(const AppInfo &other)
{
    d = other.d;
}


AppInfo::~AppInfo()
{
}

AppInfo& AppInfo::operator=(const AppInfo &other)
{
    if (this == &other) return *this; //Protect against self-assignment
    d = other.d;
    return *this;
}

QString AppInfo::id() const
{
    return d->jsonData.value(QStringLiteral("id")).toString();
}

QString AppInfo::name() const
{
    return d->jsonData.value(QStringLiteral("name")).toString();
}

QString AppInfo::description() const
{
    return d->jsonData.value(QStringLiteral("description")).toString();
}

QString AppInfo::category() const
{
    return d->jsonData.value(QStringLiteral("category")).toString();
}

QString AppInfo::company() const
{
    return d->jsonData.value(QStringLiteral("company")).toString();
}

QUrl AppInfo::iconUrl() const
{
    return QUrl::fromUserInput(d->jsonData.value(QStringLiteral("icon_url")).toString());
}

QString AppInfo::subcategory() const
{
    return d->jsonData.value(QStringLiteral("subcategory")).toString();
}

QUrl AppInfo::link() const
{
    return QUrl::fromUserInput(d->jsonData.value(QStringLiteral("link")).toString());
}

QUrl AppInfo::logoUrl() const
{
    return QUrl::fromUserInput(d->jsonData.value(QStringLiteral("logo_url")).toString());
}
