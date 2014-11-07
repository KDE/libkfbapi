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

#include <QDateTime>
#include <QFlags>

namespace KFbAPI {

/**
 * Class to represent a facebook post.
 * See https://developers.facebook.com/docs/reference/api/post/
 */

class LIBKFBAPI_EXPORT PostInfo
{
public:

    enum PostFetchOption {
        FetchNoCommentsOrLikes  = 1,
        FetchCommentsCountOnly  = 2,
        FetchLikesCountOnly     = 4,
        FetchCountsOnly         = FetchCommentsCountOnly | FetchLikesCountOnly,
        FetchAllComments        = 8,
        FetchAllLikes           = 16,
        FetchAll                = FetchAllComments | FetchAllLikes
    };

    Q_DECLARE_FLAGS(PostFetchOptions, PostFetchOption)

    PostInfo(const QJsonObject &jsonData);
    PostInfo();
    PostInfo(const PostInfo &other);
    ~PostInfo();

    PostInfo &operator=(const PostInfo &other);

    /**
     * Returns the facebook id
     */
    QString id() const;

    /**
     * Returns the creator of the post as a User Info Object
     */
    UserInfo from() const;

    /**
     * Returns the content of the post.
     */
    QString message() const;

    /**
     * Returns the picture url of  author of the post
     */
    QUrl pictureUrl() const;

    /**
     * Returns the Link of the post
     */
    QUrl link() const;

    /**
     * Returns name of the link
     */
    QString name() const;

    /**
     * Returns caption of the link
     */
    QString caption() const;

    /**
     * Returns source of the link
     */
    QUrl sourceUrl() const;

    /**
     * Returns properties of the link
     */
    QList<PropertyInfo> properties() const;

    /**
     * Returns icon of post
     */
    QUrl iconUrl() const;

    /**
     * Returns type of the post
     */
    QString type() const;

    /**
     * Returns likes of the post
     */
    LikeInfo likes() const;

    /**
     * Returns story of the post
     */
    QString story() const;

    /**
     * Returns comments of the post
     */
    CommentInfo comments() const;

    /**
     * Returns the creator app of the post
     */
    AppInfo application() const;

    /**
     * Returns the creation time as a string in "facebook format"
     */
    QString createdTimeString() const;

    /**
     * Returns the creation time in KDateTime
     */
    QDateTime createdTime() const;

    /**
     * Returns the time of the last update of the post in "facebook format"
     */
    QString updatedTimeString() const;
    /**
     * Returns the time of the last update of the post as a KDateTime
     */
    QDateTime updatedTime() const;

private:
    friend class PostCompositeJob;
    friend class PostJob;
    void setLikes(const LikeInfo &likes);
    void setComments(const CommentInfo &comments);

    class PostInfoPrivate;
    QSharedDataPointer<PostInfoPrivate> d;
};

}

Q_DECLARE_METATYPE(KFbAPI::PostInfo)
Q_DECLARE_OPERATORS_FOR_FLAGS(KFbAPI::PostInfo::PostFetchOptions)

#endif
