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

#include "likeinfo.h"
#include "userinfo.h"

#include <QJsonArray>
#include <QStringList>
#include <QDebug>

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

LikeInfo::LikeInfo(const QJsonObject &jsonData)
    : d(new LikeInfoPrivate)
{
    QJsonObject summary = jsonData.value(QStringLiteral("summary")).toObject();

    if (!summary.isEmpty() && summary.contains(QStringLiteral("total_count"))) {
        d->count = summary.value(QStringLiteral("total_count")).toInt();
    } else {
        // TODO: maybe set it to -1 to indicate "unknown" ?
        d->count = 0;
    }

    QJsonArray likesArray = jsonData.value(QStringLiteral("data")).toArray();
    for (int i = 0; i < likesArray.size(); i++) {
        d->data.append(UserInfo(likesArray.at(i).toObject()));
    }
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

QList<UserInfo> LikeInfo::data() const
{
    return d->data;
}

int LikeInfo::count() const
{
    return d->count;
}
