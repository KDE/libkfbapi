/* Copyright 2011 Pankaj Bhambhani <pankajb64@gmail.com>

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

#include "postinfo.h"

#include <QJsonArray>
#include <QDebug>


using namespace KFbAPI;

class PostInfo::PostInfoPrivate : public QSharedData {
public:
    QJsonObject jsonData;
    LikeInfo likes;
    CommentInfo comments;
};

PostInfo::PostInfo()
    : d(new PostInfoPrivate)
{
}

PostInfo::PostInfo(const QJsonObject &jsonData)
    : d(new PostInfoPrivate)
{
    d->jsonData = jsonData;
}

PostInfo::PostInfo(const PostInfo &other)
{
    d = other.d;
}

PostInfo::~PostInfo()
{
}

PostInfo& PostInfo::operator=(const PostInfo &other)
{
    if (this == &other) return *this; //Protect against self-assignment
    d = other.d;
    return *this;
}

QString PostInfo::id() const
{
    return d->jsonData.value(QStringLiteral("id")).toString();
}

UserInfo PostInfo::from() const
{
    return UserInfo(d->jsonData.value(QStringLiteral("from")).toObject());
}

QString PostInfo::message() const
{
    return d->jsonData.value(QStringLiteral("message")).toString();
}

QUrl PostInfo::pictureUrl() const
{
    return QUrl::fromUserInput(d->jsonData.value(QStringLiteral("picture")).toString());
}

QUrl PostInfo::link() const
{
    return QUrl::fromUserInput(d->jsonData.value(QStringLiteral("link")).toString());
}

QString PostInfo::name() const
{
    return d->jsonData.value(QStringLiteral("name")).toString();
}

QString PostInfo::caption() const
{
    return d->jsonData.value(QStringLiteral("caption")).toString();
}

QUrl PostInfo::sourceUrl() const
{
    return QUrl::fromUserInput(d->jsonData.value(QStringLiteral("source")).toString());
}

QList<PropertyInfo> PostInfo::properties() const
{
    QJsonArray propertyArray = d->jsonData.value(QStringLiteral("properties")).toArray();

    //TODO: cache this?
    QList<PropertyInfo> returnList;

    for (int i = 0; i < propertyArray.size(); i++) {
        returnList << PropertyInfo(propertyArray.at(i).toObject());
    }

    return returnList;
}

QUrl PostInfo::iconUrl() const
{
    return QUrl::fromUserInput(d->jsonData.value(QStringLiteral("icon")).toString());
}

QString PostInfo::type() const
{
    return d->jsonData.value(QStringLiteral("type")).toString();
}

LikeInfo PostInfo::likes() const
{
    return d->likes;
}

QString PostInfo::story() const
{
    return d->jsonData.value(QStringLiteral("story")).toString();
}

// CommentInfo PostInfo::comments() const
// {
//     return d->comments;
// }

AppInfo PostInfo::application() const
{
    return AppInfo(d->jsonData.value(QStringLiteral("application")).toObject());
}

QString PostInfo::createdTimeString() const
{
    return d->jsonData.value(QStringLiteral("created_time")).toString();
}

QDateTime PostInfo::createdTime() const
{
    return QDateTime::fromString(d->jsonData.value(QStringLiteral("created_time")).toString(), Qt::ISODate);
}

QString PostInfo::updatedTimeString() const
{
    return d->jsonData.value(QStringLiteral("updated_time")).toString();
}

QDateTime PostInfo::updatedTime() const
{
    return QDateTime::fromString(d->jsonData.value(QStringLiteral("id")).toString(), Qt::ISODate);
}

void PostInfo::setLikes(const LikeInfo &likes)
{
    d->likes = likes;
}

void PostInfo::setComments(const CommentInfo &comments)
{
    d->comments = comments;
}
