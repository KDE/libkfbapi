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
#include "util.h"
#include "commentinfo.h"

#include "propertyinfoparser_p.h"
#include "likeinfoparser_p.h"
#include "commentinfoparser_p.h"
#include "appinfoparser_p.h"
#include "userinfoparser_p.h"

#include <qjson/qobjecthelper.h>

using namespace KFbAPI;

class PostInfo::PostInfoPrivate : public QSharedData {
public:
    QString id;            /* Facebook id of the post. */
    UserInfo from;         /* Creator of the post. */
    QString message;       /* Actual content of the post. */
    QString pictureUrl;    /* Picture assocauted with the Post. */
    QString link;          /* Link associated with the post */
    QString name;          /* Name of the Link */
    QString caption;       /* Caption of the Link */
    QString description;   /* Description of the Link. */
    QString source;        /* Source of the Link */
    QList<PropertyInfo> properties;     /* Properties of the Link */
    QString icon;          /* Icon of the post */
    QString type;          /* Type of  post */
    LikeInfo likes;        /* Likes of  post */
    QString story;         /* Story of  post */
    CommentInfo comments;  /* Comments on  post */
    AppInfo application;   /*App associated with the post*/
    QString createdTime;   /* Creation time of the post. */
    QString updatedTime;   /* Last update time of the post. */
};

PostInfo::PostInfo()
    : d(new PostInfoPrivate)
{
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

void PostInfo::setId(const QString &id)
{
    d->id = id;
}

QString PostInfo::id() const
{
    return d->id;
}

void PostInfo::setFrom(const QVariantMap &from)
{
    UserInfoParser parser;
    QJson::QObjectHelper::qvariant2qobject(from, &parser);
    d->from = parser.dataObject();
}

UserInfo PostInfo::from() const
{
    return d->from;
}

QVariantMap PostInfo::fromMap() const
{
    UserInfoParser parser;
    parser.setDataObject(d->from);
    return QJson::QObjectHelper::qobject2qvariant(&parser);
}

void PostInfo::setMessage(const QString &message)
{
    d->message = message;
}

QString PostInfo::message() const
{
    return d->message;
}

QString PostInfo::pictureUrl() const
{
    return d->pictureUrl;
}

void PostInfo::setPictureUrl(const QString &pictureUrl)
{
    d->pictureUrl = pictureUrl;
}

void PostInfo::setLink(const QString &link)
{
    d->link = link;
}

QString PostInfo::link() const
{
    return d->link;
}

void PostInfo::setName(const QString &name)
{
    d->name = name;
}

QString PostInfo::name() const
{
    return d->name;
}

void PostInfo::setCaption(const QString &caption)
{
    d->caption = caption;
}

QString PostInfo::caption() const
{
    return d->caption;
}

void PostInfo::setDescription(const QString &description)
{
    d->description = description;
}

QString PostInfo::description() const
{
    return d->description;
}

void PostInfo::setSource(const QString &source)
{
    d->source = source;
}

QString PostInfo::source() const
{
    return d->source;
}

void PostInfo::setProperties(const QVariantList &properties)
{
    PropertyInfoParser parser;
    d->properties = QList<PropertyInfo>();

    Q_FOREACH (const QVariant &v, properties) {
        QVariantMap vMap = v.toMap();
        parser.setDataObject(PropertyInfo());
        QJson::QObjectHelper::qvariant2qobject(vMap, &parser);
        d->properties << parser.dataObject();
    }
}

QList<PropertyInfo> PostInfo::properties() const
{
    return d->properties;
}

QVariantList PostInfo::propertiesList() const
{
    PropertyInfoParser parser;
    QVariantList vList;

    Q_FOREACH (const PropertyInfo &propertyInfo, d->properties) {
        parser.setDataObject(propertyInfo);
        vList.append(QJson::QObjectHelper::qobject2qvariant(&parser));
    }

    return vList;
}

void PostInfo::setIcon(const QString &icon)
{
    d->icon = icon;
}

QString PostInfo::icon() const
{
    return d->icon;
}

void PostInfo::setType(const QString &type)
{
    d->type = type;
}

QString PostInfo::type() const
{
    return d->type;
}

void PostInfo::setLikes(const QVariantMap &likes)
{
    LikeInfoParser parser;
    QJson::QObjectHelper::qvariant2qobject(likes, &parser);
    d->likes = parser.dataObject();
}

LikeInfo PostInfo::likes() const
{
    return d->likes;
}

QVariantMap PostInfo::likesMap() const
{
    LikeInfoParser parser;
    parser.setDataObject(d->likes);
    return QJson::QObjectHelper::qobject2qvariant(&parser);
}

void PostInfo::setStory(const QString &story)
{
    d->story = story;
}

QString PostInfo::story() const
{
    return d->story;
}

void PostInfo::setComments(const QVariantMap &comments)
{
    CommentInfoParser parser;
    QJson::QObjectHelper::qvariant2qobject(comments, &parser);
    d->comments = parser.dataObject();
}

CommentInfo PostInfo::comments() const
{
    return d->comments;
}

QVariantMap PostInfo::commentsMap() const
{
    CommentInfoParser parser;
    parser.setDataObject(d->comments);
    return QJson::QObjectHelper::qobject2qvariant(&parser);
}

void PostInfo::setApplication(const QVariantMap &application)
{
    AppInfoParser parser;
    QJson::QObjectHelper::qvariant2qobject(application, &parser);
    d->application = parser.dataObject();
}

AppInfo PostInfo::application() const
{
    return d->application;
}

QVariantMap PostInfo::applicationMap() const
{
    AppInfoParser parser;
    parser.setDataObject(d->application);
    return QJson::QObjectHelper::qobject2qvariant(&parser);
}

void PostInfo::setCreatedTimeString(const QString &createdTime)
{
    d->createdTime = createdTime;
}

QString PostInfo::createdTimeString() const
{
    return d->createdTime;
}

KDateTime PostInfo::createdTime() const
{
    return facebookTimeToKDateTime(d->createdTime);
}

void PostInfo::setUpdatedTimeString(const QString &updatedTime)
{
    d->updatedTime = updatedTime;
}

QString PostInfo::updatedTimeString() const
{
    return d->updatedTime;
}

KDateTime PostInfo::updatedTime() const
{
    return facebookTimeToKDateTime(d->updatedTime);
}
