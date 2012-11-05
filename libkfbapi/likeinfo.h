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

#ifndef KFBAPI_LIKEINFO_H
#define KFBAPI_LIKEINFO_H

#include "libkfbapi_export.h"
#include "userinfo.h"

#include <qjson/qobjecthelper.h>
#include <QObject>

namespace KFbAPI {

/**
 * Class to represent likes on a facebook post
 */

class LIBKFBAPI_EXPORT LikeInfo
{
public:
    LikeInfo();
    LikeInfo(const LikeInfo &other);
    ~LikeInfo();

    LikeInfo &operator=(const LikeInfo &other);

    /**
     * Set the data of this like (list of people who like the post)
     * @param data the like data
     */
    void setData(const QVariantList &data);
    /**
     * Returns the like data
     */
    QList<UserInfo> data() const;
    /**
     * Return the like data as VariantList
     */
    QVariantList dataList() const;

    /**
     * Set the count of this like (number of people who like the post)
     * @param count the like count
     */
    void setCount(const int &count);
    /**
     * Returns the like count
     */
    int count() const;

    /**
     * Returns relative REST path w.r.t FacebookObject, "/" included
     */
    QString path() const;

private:
    class LikeInfoPrivate;
    QSharedDataPointer<LikeInfoPrivate> d;
};

}

#endif
