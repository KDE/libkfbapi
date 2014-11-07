/* Copyright (C) 2014 Martin Klapetek <mklapetek@kde.org>

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

#ifndef POSTCOMPOSITEJOB_H
#define POSTCOMPOSITEJOB_H

#include "libkfbapi_export.h"
#include "postinfo.h"

#include <KJob>

namespace KFbAPI {

class PostCompositeJobPrivate;

/**
 * A class that will fetch posts and also likes and/or comments,
 * all encapsulated in a single KJob. Useful for retrieving it all
 * at once.
 *
 * It is capable of fetching one single post by its id, multiple
 * posts by their ids or last posts from home timeline. In order
 * to retrieve the latest posts from the timeline, pass empty
 * QString as postId. To set what parts should be fetched, use
 * the options param.
 *
 * It will first fetch the requested posts and only then issues
 * subjobs for getting likes and/or comments
 */
class LIBKFBAPI_EXPORT PostCompositeJob : public KJob
{
    Q_OBJECT

public:
    /**
     * Constructs the composite job of getting the posts passed in postIds
     * and consequently fetching likes and/or comments, based on the options
     * passed in options param
     *
     * @param postIds The IDs of posts to fetch
     * @param options The fetching options, sets if and how to fetch likes and/or comments
     *                for the given posts IDs
     * @param accessToken Facebook access token
     */
    PostCompositeJob(const QStringList &postIds, const PostInfo::PostFetchOptions &options, const QString &accessToken, QObject *parent = 0);

    /**
     * Constructs the composite job of getting the posts specified in postId
     * and consequently fetching likes and/or comments, based on the options
     * passed in options param. Leave empty postId to fetch recent posts
     *
     * @param postId The ID of the post to fetch
     * @param options The fetching options, sets if and how to fetch likes and/or comments
     *                for the given posts IDs
     * @param accessToken Facebook access token
     */
    PostCompositeJob(const QString &postId, const PostInfo::PostFetchOptions &options, const QString &accessToken, QObject *parent = 0);
    ~PostCompositeJob();

    /**
     * Starts sending the request to the server
     */
    virtual void start();

    /**
     * The list of retrieved posts, including likes and/or comments
     * if they were specified in options
     */
    QList<PostInfo> posts() const;

private Q_SLOTS:
    void onPostJobFinished(KJob *job);
    void onPostListJobFinished(KJob *job);
    void onLikesJobFinished(KJob *job);
    void onCommentsJobFinished(KJob *job);

protected:
    virtual bool doKill();

private:
    PostCompositeJobPrivate * const d_ptr;
    Q_DECLARE_PRIVATE(PostCompositeJob)
};

};

#endif // POSTCOMPOSITEJOB_H
