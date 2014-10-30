/* Copyright 2012 Pankaj Bhambhani <pankajb64@gmail.com>
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

#ifndef KFBAPI_PROPERTYINFO_H
#define KFBAPI_PROPERTYINFO_H

#include "libkfbapi_export.h"

#include <QSharedPointer>
#include <QJsonObject>

namespace KFbAPI {

/**
 * Class to represent a property associated with a facebook post
 */

class LIBKFBAPI_EXPORT PropertyInfo
{
public:
    PropertyInfo(const QJsonObject &jsonData);
    PropertyInfo();
    PropertyInfo(const PropertyInfo &other);
    ~PropertyInfo();

    PropertyInfo &operator=(const PropertyInfo &other);

    /**
    * Returns the property name
    */
    QString name() const;

    /**
    * Returns the property text
    */
    QString text() const;

    /**
    * Returns the property href
    */
    QString href() const;

private:
    class PropertyInfoPrivate;
    QSharedDataPointer<PropertyInfoPrivate> d;
 };

}

#endif
