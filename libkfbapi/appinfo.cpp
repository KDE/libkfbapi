/* Copyright 2012 Pankaj Bhambhani <pankajb64@gmail.com>

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
    QString id;            /* Facebook id of the Application. */
    QString name;          /* Name of the Application */
    QString description;   /* Description of the Application. */
    QString category;      /* Category of the Application */
    QString company;       /* Company of the Application */
    QString iconUrl;       /* IconUrl of the Application */
    QString subcategory;   /* Subcategory of the Application */
    QString link;          /* Link of the Application */
    QString logoUrl;       /* LogoUrl of the Application */
};

AppInfo::AppInfo()
    : d(new AppInfoPrivate)
{
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

void AppInfo::setId(const QString &id)
{
    d->id = id;
}

QString AppInfo::id() const
{
    return d->id;
}

void AppInfo::setName(const QString &name)
{
    d->name = name;
}

QString AppInfo::name() const
{
    return d->name;
}

void AppInfo::setDescription(const QString &description)
{
    d->description = description;
}

QString AppInfo::description() const
{
    return d->description;
}

void AppInfo::setCategory(const QString &category)
{
    d->category = category;
}

QString AppInfo::category() const
{
    return d->category;
}

void AppInfo::setCompany(const QString &company)
{
    d->company = company;
}

QString AppInfo::company() const
{
    return d->company;
}

void AppInfo::setIconUrl(const QString &iconUrl)
{
    d->iconUrl = iconUrl;
}

QString AppInfo::iconUrl() const
{
    return d->iconUrl;
}

void AppInfo::setSubcategory(const QString &subCategory)
{
    d->subcategory = subCategory;
}

QString AppInfo::subcategory() const
{
    return d->subcategory;
}

void AppInfo::setLink(const QString &link)
{
    d->link = link;
}

QString AppInfo::link() const
{
    return d->link;
}

void AppInfo::setLogoUrl(const QString &logoUrl)
{
    d->logoUrl = logoUrl;
}

QString AppInfo::logoUrl() const
{
    return d->logoUrl;
}
