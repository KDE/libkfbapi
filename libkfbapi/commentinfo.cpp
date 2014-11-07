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

#include "commentinfo.h"

#include <QJsonArray>

using namespace KFbAPI;

class CommentData::CommentDataPrivate : public QSharedData {
public:
    QJsonObject jsonData;
};

CommentData::CommentData(const QJsonObject &jsonData)
    : d(new CommentDataPrivate)
{
    d->jsonData = jsonData;
}

CommentData::CommentData()
    : d(new CommentDataPrivate)
{
}

CommentData::CommentData(const CommentData &other)
{
    d = other.d;
}

CommentData::~CommentData()
{
}

CommentData& CommentData::operator=(const CommentData &other)
{
    if (this == &other) return *this; //Protect against self-assignment
    d = other.d;
    return *this;
}

QString CommentData::id() const
{
    return d->jsonData.value(QStringLiteral("id")).toString();
}

UserInfo CommentData::from() const
{
    return UserInfo(d->jsonData.value(QStringLiteral("from")).toObject());
}

QString CommentData::message() const
{
    return d->jsonData.value(QStringLiteral("message")).toString();
}

QString CommentData::createdTimeString() const
{
    return d->jsonData.value(QStringLiteral("created_time")).toString();
}

QDateTime CommentData::createdTime() const
{
    return QDateTime::fromString(d->jsonData.value(QStringLiteral("created_time")).toString(), Qt::ISODate);
}

int CommentData::likes() const
{
    return d->jsonData.value(QStringLiteral("like_count")).toInt();
}

//============================================================================

class CommentInfo::CommentInfoPrivate : public QSharedData {
public:
    QList<CommentData> data;       /*  Data of comment. */
    int count;                     /* Count  of comment. */
};

CommentInfo::CommentInfo(const QJsonObject &jsonData)
    : d(new CommentInfoPrivate)
{
    QJsonObject summary = jsonData.value(QStringLiteral("summary")).toObject();

    if (!summary.isEmpty() && summary.contains(QStringLiteral("total_count"))) {
        d->count = summary.value(QStringLiteral("total_count")).toInt();
    } else {
        // TODO: maybe set it to -1 to indicate "unknown" ?
        d->count = 0;
    }

    QJsonArray dataArray = jsonData.value(QStringLiteral("data")).toArray();
    for (int i = 0; i < dataArray.size(); i++) {
        d->data.append(CommentData(dataArray.at(i).toObject()));
    }
}

CommentInfo::CommentInfo()
    : d(new CommentInfoPrivate)
{
}

CommentInfo::CommentInfo(const CommentInfo& other)
{
    d = other.d;
}

CommentInfo::~CommentInfo()
{
}

CommentInfo& CommentInfo::operator=(const CommentInfo &other)
{
    if (this == &other) return *this; //Protect against self-assignment
    d = other.d;
    return *this;
}

QList<CommentData> CommentInfo::data() const
{
    return d->data;
}

int CommentInfo::count() const
{
    return d->count;
}
