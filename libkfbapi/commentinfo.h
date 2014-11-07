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

#ifndef KFBAPI_COMMENTINFO_H
#define KFBAPI_COMMENTINFO_H

#include "libkfbapi_export.h"
#include "userinfo.h"

#include <QDateTime>
#include <QJsonObject>

namespace KFbAPI {

/**
 * Class that represents data to be held by comment
 */
class LIBKFBAPI_EXPORT CommentData
{
public:
    CommentData(const QJsonObject &jsonData);
    CommentData();
    CommentData(const CommentData &other);
    ~CommentData();

    CommentData &operator=(const CommentData &other);

    /**
     * Returns the facebook id of comment
     */
    QString id() const;

    /**
     * Returns the person who commented the post
     */
    UserInfo from() const;

    /**
     * Returns the content of the comment.
     */
    QString message() const;

    /**
     * Returns the creation time as a string in "facebook format"
     */
    QString createdTimeString() const;
    /**
     * Returns the creation time in QDateTime
     */
    QDateTime createdTime() const;

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
    CommentInfo(const QJsonObject &jsonData);
    CommentInfo();
    CommentInfo(const CommentInfo &other);
    ~CommentInfo();

    CommentInfo &operator=(const CommentInfo &other);

    /**
     * Returns the comment data
     */
    QList<CommentData> data() const;

    /**
     * Returns the comment count
     */
    int count() const;

private:
    class CommentInfoPrivate;
    QSharedDataPointer<CommentInfoPrivate> d;
};

}

#endif
