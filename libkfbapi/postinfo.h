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

#ifndef KFBAPI_POSTINFO_H
#define KFBAPI_POSTINFO_H

#include "libkfbapi_export.h"
#include "userinfo.h"
#include "propertyinfo.h"
#include "appinfo.h"
#include "commentinfo.h"
#include "likeinfo.h"

#include <KDateTime>

namespace KFbAPI {

/**
 * Class to represent a facebook post.
 * See https://developers.facebook.com/docs/reference/api/post/
 */

class LIBKFBAPI_EXPORT PostInfo
{
public:
    PostInfo();
    PostInfo(const PostInfo &other);
    ~PostInfo();

    PostInfo &operator=(const PostInfo &other);

    /**
     * Set the facebook id of this post
     * @param id the facebook id
     */
    void setId(const QString &id);
    /**
     * Returns the facebook id
     */
    QString id() const;

    /**
     * Set the user who wrote the post as a QVariantMap
     * @param from the creator of the post
     */
    void setFrom(const QVariantMap &from);
    /**
     * Returns the creator of the post as a User Info Object
     */
    UserInfo from() const;

    /**
     * Returns the creator of the post as a QVariantMap
     */
    QVariantMap fromMap() const;

    /**
     * Set the actual content of the post
     * @param message The actual content of the post
     */
    void setMessage(const QString &message);
    /**
     * Returns the content of the post.
     */
    QString message() const;

    /**
     * Set picture url of  author of the post
     * @param picture url - url of  author of the post
     */
    void setPictureUrl(const QUrl &pictureUrl);
    /**
     * Returns the picture url of  author of the post
     */
    QUrl pictureUrl() const;

    /**
     * Set link associated the post
     * @param link the link of the post
     */
    void setLink(const QUrl &link);
    /**
     * Returns the Link of the post
     */
    QUrl link() const;

    /**
     * Set name of link
     * @param name  of the link
     */
    void setName(const QString &name);
    /**
     * Returns name of the link
     */
    QString name() const;

    /**
     * Set caption of link
     * @param caption  of the link
     */
    void setCaption(const QString &caption);
    /**
     * Returns caption of the link
     */
    QString caption() const;

    /**
     * Set description of the post
     * @param description the description of the post
     */
    void setDescription(const QString &description);
    /**
     * Returns the description of the post
     */
    QString description() const;

    /**
     * Set source of link (url of video for e.g.)
     * @param source  of the link
     */
    void setSourceUrl(const QUrl &source);
    /**
     * Returns source of the link
     */
    QUrl sourceUrl() const;

    /**
     * Set properties aoosicated with the link (length of video for e.g)
     * @param properties  of the link
     */
    void setProperties(const QVariantList &properties);
    /**
     * Returns properties of the link
     */
    QList<PropertyInfo> properties() const;

    /**
     * Returns properties of the post as a QVariantList
     */
    QVariantList propertiesList() const;

    /**
     * Set icon of post (represents type of post)
     * @param icon  of post
     */
    void setIcon(const QString &icon);
    /**
     * Returns icon of post
     */
    QString icon() const;

    /**
     * Set type of post
     * @param type  of the post
     */
    void setType(const QString &type);
    /**
     * Returns type of the post
     */
    QString type() const;

    /**
     * Set likes of post
     * @param likes  of the post
     */
    void setLikes(const QVariantMap &likes);
    /**
     * Returns likes of the post
     */
    LikeInfo likes() const;

    /**
     * Returns likes of the post as a Variant Map
     */
    QVariantMap likesMap() const;
    /**
     * Set story of post (generated by app)
     * @param story  of the post
     */
    void setStory(const QString &story);
    /**
     * Returns story of the post
     */
    QString story() const;

    /**
     * Set comments of post
     * @param comments  of the post
     */
    void setComments(const QVariantMap &comments);
    /**
     * Returns comments of the post
     */
    CommentInfo comments() const;

    /**
     * Returns comments of the post as a Variant Map
     */
    QVariantMap commentsMap() const;

     /**
     * Set the app that created the post
     * @param app the app that created the post
     */
    void setApplication(const QVariantMap &app);
    /**
     * Returns the creator app of the post
     */
    AppInfo application() const;

    /**
     * Returns the creator app of the post as a QVariantMap
     */
    QVariantMap applicationMap() const;

    /**
     * Set the creation time of the post
     * @param createdTime Time in "facebook format"
     */
    void setCreatedTimeString(const QString &createdTime);
    /**
     * Returns the creation time as a string in "facebook format"
     */
    QString createdTimeString() const;
    /**
     * Returns the creation time in KDateTime
     */
    KDateTime createdTime() const;

    /**
     * Set the time of the last update of the post
     * @param updatedTime The time, in "facebook format", of the last update of
     *                    the post.
     */
    void setUpdatedTimeString(const QString &updatedTime);
    /**
     * Returns the time of the last update of the post in "facebook format"
     */
    QString updatedTimeString() const;
    /**
     * Returns the time of the last update of the post as a KDateTime
     */
    KDateTime updatedTime() const;

private:
    class PostInfoPrivate;
    QSharedDataPointer<PostInfoPrivate> d;
};

}

Q_DECLARE_METATYPE(KFbAPI::PostInfo)

#endif
