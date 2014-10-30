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

#ifndef KFBAPI_APPINFO_H
#define KFBAPI_APPINFO_H

#include "libkfbapi_export.h"

#include <QSharedPointer>
#include <QUrl>
#include <QJsonObject>

namespace KFbAPI {

/**
 * Class to represent a facebook application. See https://developers.facebook.com/docs/reference/api/application/
 */

class LIBKFBAPI_EXPORT AppInfo
{
public:
    AppInfo();
    AppInfo(const QJsonObject &jsonData);
    AppInfo(const AppInfo &other);
    ~AppInfo();

    AppInfo &operator=(const AppInfo &other);

    /**
     * Set the facebook id of this application
     * @param id the facebook id
     */
    void setId(const QString &id);
    /**
     * Returns the facebook id
     */
    QString id() const;

    /**
     * Returns the facebook name
     */
    QString name() const;

    /**
     * Returns the description
     */
    QString description() const;

    /**
     * Returns the category
     */
    QString category() const;

    /**
     * Returns the company
     */
    QString company() const;

    /**
     * Returns the Icon Url
     */
    QUrl iconUrl() const;

    /**
     * Returns the subcategory
     */
    QString subcategory() const;

    /**
     * Returns the Logo URL
     */
    QUrl logoUrl() const;

    /**
     * Returns the link
     */
    QUrl link() const;

private:
    class AppInfoPrivate;
    QSharedDataPointer<AppInfoPrivate> d;
};

}

#endif
