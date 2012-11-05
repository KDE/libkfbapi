/* Copyright 2012 Pankaj Bhambhani <pankajb64@gmail.com>

   This library is free software; you can redistribute it and/or modify
   it under the terms of the GNU Library General Public License as published
   by the Free Software Foundation; either version 2 of the License or
   (at your option ) version 3 or, at the discretion of KDE e.V.
   (which shall act as a proxy as in section 14 of the GPLv3 ), any later version.

   This library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Library General Public License for more details.

   You should have received a copy of the GNU Library General Public License
   along with this library; see the file COPYING.LIB.  If not, write to
   the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.
*/

#include "propertyinfo.h"

using namespace KFbAPI;

class PropertyInfo::PropertyInfoPrivate : public QSharedData {
public:
    QString name;      /* Name of the property. */
    QString text;      /* Text of the property. */
    QString href;      /* Href Link of the property. */
};

PropertyInfo::PropertyInfo()
    : d(new PropertyInfoPrivate)
{
}

PropertyInfo::PropertyInfo(const PropertyInfo &other)
{
    d = other.d;
}

PropertyInfo::~PropertyInfo()
{
}

PropertyInfo& PropertyInfo::operator=(const PropertyInfo &other)
{
    if (this == &other) return *this; //Protect against self-assignment
    d = other.d;
    return *this;
}

void PropertyInfo::setName(const QString &name)
{
    d->name = name;
}

QString PropertyInfo::name() const
{
    return d->name;
}

void PropertyInfo::setText(const QString &text)
{
    d->text = text;
}

QString PropertyInfo::text() const
{
    return d->text;
}

void PropertyInfo::setHref(const QString &href)
{
    d->href = href;
}

QString PropertyInfo::href() const
{
    return d->href;
}
