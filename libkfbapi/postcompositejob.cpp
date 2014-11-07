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

#include "postcompositejob.h"
#include "postslistjob.h"
#include "postjob.h"
#include "likesjob.h"
#include "commentsjob.h"

#include <QDebug>

using namespace KFbAPI;

class KFbAPI::PostCompositeJobPrivate {
public:
    PostCompositeJobPrivate(const QStringList &postIds, const PostInfo::PostFetchOptions &options, const QString &accessToken, PostCompositeJob *q);

    void jobRef();
    void jobDeref();

    QString accessToken;
    QStringList postIds;
    PostInfo::PostFetchOptions options;
    QHash<QString, PostInfo> posts;
    QList<LikesJob*> likeJobs;
    QList<CommentsJob*> commentJobs;
    uint jobsRef;

private:
    PostCompositeJob *q;
};

PostCompositeJobPrivate::PostCompositeJobPrivate(const QStringList &postIds, const PostInfo::PostFetchOptions &options, const QString &accessToken, PostCompositeJob *q)
{
    this->q = q;
    this->options = options;
    this->accessToken = accessToken;
    this->postIds = postIds;
    this->jobsRef = 0;
}

void PostCompositeJobPrivate::jobRef()
{
    jobsRef++;
}

void PostCompositeJobPrivate::jobDeref()
{
    jobsRef--;

    if (jobsRef == 0) {
        q->emitResult();

    }
}

//----------------------------------------------------------------------------------

PostCompositeJob::PostCompositeJob(const QStringList &postIds, const PostInfo::PostFetchOptions &options, const QString &accessToken, QObject *parent)
    : KJob(parent),
      d_ptr(new KFbAPI::PostCompositeJobPrivate(postIds, options, accessToken, this))
{

}

PostCompositeJob::PostCompositeJob(const QString &postId, const PostInfo::PostFetchOptions &options, const QString &accessToken, QObject *parent)
    : KJob(parent),
      d_ptr(new KFbAPI::PostCompositeJobPrivate(postId.isEmpty() ? QStringList() : QStringList() << postId, options, accessToken, this))
{

}

PostCompositeJob::~PostCompositeJob()
{
}

void PostCompositeJob::start()
{
    Q_D(PostCompositeJob);

    if (d->postIds.isEmpty()) {
        PostsListJob *postListJob = new PostsListJob(d->accessToken, this);
        connect(postListJob, &KFbAPI::PostsListJob::finished, this, &KFbAPI::PostCompositeJob::onPostListJobFinished);
        postListJob->start();
    } else {
        PostJob *postJob;

        if (d->postIds.size() == 1) {
            postJob = new PostJob(d->postIds.first(), d->accessToken, this);
        } else {
            postJob = new PostJob(d->postIds, d->accessToken, this);
        }

        connect(postJob, &KFbAPI::PostJob::finished, this, &KFbAPI::PostCompositeJob::onPostJobFinished);
        postJob->start();
    }

    d->jobRef();
}

bool PostCompositeJob::doKill()
{
    Q_D(PostCompositeJob);

    if (d->jobsRef != 0) {
        //TODO: kill the jobs
    }
    return KJob::doKill();
}

void PostCompositeJob::onPostJobFinished(KJob *job)
{
    Q_D(PostCompositeJob);

    d->jobDeref();

    PostJob *postJob = qobject_cast<PostJob*>(job);
    if (!postJob) {
        qWarning() << "Unable to cast job to PostJob";
        return;
    }

    bool shouldStartLikesJob = (d->options & PostInfo::FetchLikesCountOnly || d->options & PostInfo::FetchAllLikes);
    bool shouldStartCommentsJob = (d->options & PostInfo::FetchCommentsCountOnly || d->options & PostInfo::FetchAllComments);

    Q_FOREACH (const PostInfo &post, postJob->postInfo()) {
        QString postId = post.id();
        d->posts.insert(postId, post);

        if (shouldStartLikesJob) {
            d->likeJobs << new LikesJob(postId, d->options, d->accessToken, this);
            d->likeJobs.last()->setProperty("postId", postId);
        }

        if (shouldStartCommentsJob) {
            d->commentJobs << new CommentsJob(postId, d->options, d->accessToken, this);
            d->commentJobs.last()->setProperty("postId", postId);
        }
    }

    if (!d->likeJobs.isEmpty()) {
        connect(d->likeJobs.first(), &KFbAPI::LikesJob::finished, this, &KFbAPI::PostCompositeJob::onLikesJobFinished);
        d->likeJobs.first()->start();
        d->jobRef();
    }

    if (!d->commentJobs.isEmpty()) {
        connect(d->commentJobs.first(), &KFbAPI::CommentsJob::finished, this, &KFbAPI::PostCompositeJob::onCommentsJobFinished);
        d->commentJobs.first()->start();
        d->jobRef();
    }
}

void PostCompositeJob::onLikesJobFinished(KJob *job)
{
    Q_D(PostCompositeJob);

    d->jobDeref();

    LikesJob *likesJob = qobject_cast<LikesJob*>(job);
    if (!likesJob) {
        qWarning() << "Unable to cast job to LikesJob";
        return;
    }

    const QString postId = likesJob->property("postId").toString();
    d->posts[postId].setLikes(likesJob->likeInfo());

    if (!d->likeJobs.isEmpty()) {
        LikesJob *newLikesJob = d->likeJobs.takeFirst();
        connect(newLikesJob, &KFbAPI::LikesJob::finished, this, &KFbAPI::PostCompositeJob::onLikesJobFinished);
        newLikesJob->start();
        d->jobRef();
    }
}

void PostCompositeJob::onPostListJobFinished(KJob *job)
{
    Q_D(PostCompositeJob);

    d->jobDeref();

    PostsListJob *postsJob = qobject_cast<PostsListJob*>(job);
    if (!postsJob) {
        qWarning() << "Unable to cast job to PostsListJob";
        return;
    }

    bool shouldStartLikesJob = (d->options & PostInfo::FetchLikesCountOnly || d->options & PostInfo::FetchAllLikes);
    bool shouldStartCommentsJob = (d->options & PostInfo::FetchCommentsCountOnly || d->options & PostInfo::FetchAllComments);

    Q_FOREACH (const PostInfo &post, postsJob->posts()) {
        QString postId = post.id();
        d->posts.insert(postId, post);

        if (shouldStartLikesJob) {
            d->likeJobs << new LikesJob(postId, d->options, d->accessToken, this);
            d->likeJobs.last()->setProperty("postId", postId);
        }

        if (shouldStartCommentsJob) {
            d->commentJobs << new CommentsJob(postId, d->options, d->accessToken, this);
            d->commentJobs.last()->setProperty("postId", postId);
        }
    }

    if (!d->likeJobs.isEmpty()) {
        connect(d->likeJobs.first(), &KFbAPI::LikesJob::finished, this, &KFbAPI::PostCompositeJob::onLikesJobFinished);
        d->likeJobs.takeFirst()->start();
        d->jobRef();
    }

    if (!d->commentJobs.isEmpty()) {
        connect(d->commentJobs.first(), &KFbAPI::CommentsJob::finished, this, &KFbAPI::PostCompositeJob::onCommentsJobFinished);
        d->commentJobs.takeFirst()->start();
        d->jobRef();
    }
}

void PostCompositeJob::onCommentsJobFinished(KJob *job)
{
    Q_D(PostCompositeJob);

    d->jobDeref();

    CommentsJob *commentsJob = qobject_cast<CommentsJob*>(job);
    if (!commentsJob) {
        qWarning() << "Unable to cast job to CommentsJob";
        return;
    }

    const QString postId = commentsJob->property("postId").toString();
    d->posts[postId].setComments(commentsJob->commentInfo());

    if (!d->commentJobs.isEmpty()) {
        CommentsJob *newCommentsJob = d->commentJobs.takeFirst();
        connect(newCommentsJob, &KFbAPI::CommentsJob::finished, this, &KFbAPI::PostCompositeJob::onCommentsJobFinished);
        newCommentsJob->start();
        d->jobRef();
    }
}

QList<PostInfo> PostCompositeJob::posts() const
{
    Q_D(const PostCompositeJob);

    return d->posts.values();
}
