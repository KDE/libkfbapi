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

#include "likeinfo.h"
#include "userinfoparser_p.h"

#include <qjson/qobjecthelper.h>

using namespace KFbAPI;

class LikeInfo::LikeInfoPrivate : public QSharedData {
public:
    QList<UserInfo> data;   /*  Data of like. */
    int count;                 /* Count  of like. */
};

LikeInfo::LikeInfo()
    : d(new LikeInfoPrivate)
{
}

LikeInfo::LikeInfo(const LikeInfo &other)
{
    d = other.d;
}

LikeInfo::~LikeInfo()
{
}

LikeInfo& LikeInfo::operator=(const LikeInfo &other)
{
    if (this == &other) return *this; //Protect against self-assignment
    d = other.d;
    return *this;
}

void LikeInfo::setData(const QVariantList &data)
{
    UserInfoParser parser;
    d->data = QList<UserInfo>();

    Q_FOREACH (const QVariant &v, data) {
        QVariantMap vMap = v.toMap();
        parser.setDataObject(UserInfo());
        QJson::QObjectHelper::qvariant2qobject(vMap, &parser);
        d->data << parser.dataObject();
    }
}

QList<UserInfo> LikeInfo::data() const
{
    return d->data;
}

QVariantList LikeInfo::dataList() const
{
    UserInfoParser parser;
    QVariantList list;

    Q_FOREACH (const UserInfo &user, d->data) {
        parser.setDataObject(user);
        list.append(QJson::QObjectHelper::qobject2qvariant(&parser));
    }

    return list;
}

void LikeInfo::setCount(const int &count)
{
    d->count = count;
}

int LikeInfo::count() const
{
    return d->count;
}

QString LikeInfo::path() const
{
    return "/likes";
}
