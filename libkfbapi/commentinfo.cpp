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

#include "commentinfo.h"
#include "util.h"
#include "userinfoparser_p.h"
#include "commentinfoparser_p.h"

using namespace KFbAPI;

class CommentData::CommentDataPrivate : public QSharedData {
public:
    QString id;            /* Facebook id of comment. */
    UserInfo from;         /* Person who commented on the post. */
    QString message;       /* Actual content of the comment. */
    QString createdTime;   /* Creation time of the comment. */
    int likes;             /* No. of likes on  the comment. */
};

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

void CommentData::setId(const QString &id)
{
    d->id = id;
}

QString CommentData::id() const
{
    return d->id;
}

void CommentData::setFrom(const QVariantMap &from)
{
    UserInfoParser parser;
    QJson::QObjectHelper::qvariant2qobject(from, &parser);
    d->from = parser.dataObject();
}

UserInfo CommentData::from() const
{
    return d->from;
}

QVariantMap CommentData::fromMap() const
{
    UserInfoParser parser;
    parser.setDataObject(d->from);
    return QJson::QObjectHelper::qobject2qvariant(&parser);
}

void CommentData::setMessage(const QString &message)
{
    d->message = message;
}

QString CommentData::message() const
{
    return d->message;
}

void CommentData::setCreatedTimeString(const QString &createdTime)
{
    d->createdTime = createdTime;
}

QString CommentData::createdTimeString() const
{
    return d->createdTime;
}

KDateTime CommentData::createdTime() const
{
    return facebookTimeToKDateTime(d->createdTime);
}

void CommentData::setLikes(int likes)
{
    d->likes = likes;
}

int CommentData::likes() const
{
    return d->likes;
}

//============================================================================

class CommentInfo::CommentInfoPrivate : public QSharedData {
public:
    QList<CommentData> data;       /*  Data of comment. */
    int count;                     /* Count  of comment. */
};

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

void CommentInfo::setData(const QVariantList &data)
{
    d->data = QList<CommentData>();
    CommentDataParser parser;

    Q_FOREACH (const QVariant &v, data) {
        QVariantMap vMap = v.toMap();
        CommentData commentData;
        parser.setDataObject(commentData);

        QJson::QObjectHelper::qvariant2qobject(vMap, &parser);
        d->data << parser.dataObject();
    }
}

QList<CommentData> CommentInfo::data() const
{
    return d->data;
}

QVariantList CommentInfo::dataList() const
{
    QVariantList list;

    CommentDataParser parser;

    Q_FOREACH (const CommentData &comment, d->data) {
        parser.setDataObject(comment);
        list.append(QJson::QObjectHelper::qobject2qvariant(&parser));
    }

    return list;
}

void CommentInfo::setCount(int count)
{
    d->count = count;
}

int CommentInfo::count() const
{
    return d->count;
}

QString CommentInfo::path() const
{
    return "/comments";
}
