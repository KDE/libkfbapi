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

#ifndef KFBAPI_COMMENTINFO_H
#define KFBAPI_COMMENTINFO_H

#include "libkfbapi_export.h"
#include "userinfo.h"

#include <KDateTime>

namespace KFbAPI {

/**
 * Class that represents data to be held by comment
 */
class LIBKFBAPI_EXPORT CommentData
{
public:
    CommentData();
    CommentData(const CommentData &other);
    ~CommentData();

    CommentData &operator=(const CommentData &other);

    /**
     * Set the facebook id of comment
     * @param id the facebook id
     */
    void setId(const QString &id);
    /**
     * Returns the facebook id of comment
     */
    QString id() const;

    /**
     * Set the person who commented the post
     * @param from the person
     */
    void setFrom(const QVariantMap &from);
    /**
     * Returns the person who commented the post
     */
    UserInfo from() const;
    /**
     * Returns the person who commented the post as a QVariantMap
     */
    QVariantMap fromMap() const;
    /**
     * Set the actual content of the comment
     * @param message The actual content of the comment
     */
    void setMessage(const QString &message);
    /**
     * Returns the content of the comment.
     */
    QString message() const;

    /**
     * Set the creation time of the comment
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
     * Set the no. of likes of comment
     * @param likes the no. of likes
     */
    void setLikes(int likes);
    /**
     * Returns the no. of likes
     */
    int likes() const;


private:
    class CommentDataPrivate;
    QSharedDataPointer<CommentDataPrivate> d;
};

/**
 * Class to represent a facebook comment . See https://developers.facebook.com/docs/reference/api/Comment/
 */
class LIBKFBAPI_EXPORT CommentInfo
{
public:
    CommentInfo();
    CommentInfo(const CommentInfo &other);
    ~CommentInfo();

    CommentInfo &operator=(const CommentInfo &other);

    /**
     * Set the data of this like (list of people who like the post)
     * @param data the like data
     */
    void setData(const QVariantList &data);
    /**
     * Returns the comment data
     */
    QList<CommentData> data() const;
    /**
     * Returns the comment data as Variant List
     */
    QVariantList dataList() const;

    /**
     * Set the count of this like (number of people who like the post)
     * @param count the like count
     */
    void setCount(int count);
    /**
     * Returns the comment count
     */
    int count() const;

    /**
     * Returns relative REST path w.r.t FacebookObject, "/" included
     * */
    QString path() const;


private:
    class CommentInfoPrivate;
    QSharedDataPointer<CommentInfoPrivate> d;
};


}

#endif
