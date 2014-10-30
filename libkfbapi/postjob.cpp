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

#include "postjob.h"
#include "facebookjobs_p.h"
#include "likesjob.h"

#include <QDebug>

using namespace KFbAPI;

class KFbAPI::PostJobPrivate : public KFbAPI::FacebookGetJobPrivate {
public:
    PostJobPrivate() {
        fields << QStringLiteral("application")
               << QStringLiteral("caption")
               << QStringLiteral("created_time")
               << QStringLiteral("from")
               << QStringLiteral("icon")
               << QStringLiteral("id")
               << QStringLiteral("link")
               << QStringLiteral("message")
               << QStringLiteral("name")
               << QStringLiteral("picture")
               << QStringLiteral("properties")
               << QStringLiteral("source")
               << QStringLiteral("story")
               << QStringLiteral("type")
               << QStringLiteral("updated_time");
    }

    QHash<QString, PostInfo> posts;
    QStringList fields;
//     PostInfo::PostFetchOptions options;
//     QString accessToken;
};

//-----------------------------------------------------------------------------

PostJob::PostJob(const QString &postId, const QString &accessToken, QObject *parent)
    : FacebookGetIdJob(*new PostJobPrivate, postId, accessToken, parent)
{
    Q_D(PostJob);

//     d->options = options;
//     d->accessToken = accessToken;
//     setFields(d->fields);
}

PostJob::PostJob(const QStringList &postIds, const QString &accessToken, QObject *parent)
    : FacebookGetIdJob(*new PostJobPrivate, postIds, accessToken, parent)
{
    Q_D(PostJob);

//     d->options = options;
//     d->accessToken = accessToken;
//     setFields(d->fields);
}

QList<PostInfo> PostJob::postInfo() const
{
    Q_D(const PostJob);
    return d->posts.values();
}

void PostJob::handleSingleData(const QJsonDocument &data)
{
    Q_D(PostJob);
    PostInfo post(data.object());
    d->posts.insert(post.id(), post);
/*
    if (d->options & PostInfo::FetchAllLikes || d->options & PostInfo::FetchLikesCountOnly) {
        // start likes job for the post id, keep a map so the result can be added to the post
        LikesJob *likesJob = new LikesJob(post.id(), d->options, d->accessToken);
        connect(likesJob, &KFbAPI::LikesJob::finished, [&post](KJob *job) mutable {
            LikesJob *likesJob2 = qobject_cast<LikesJob*>(job);

            if (job->error()) {
                qDebug() << "Erroor! Erroor!" << job->errorString() << job->errorText();
            }

            if (!likesJob2) {
                qWarning() << "Casting job to LikesJob failed";
//                 return;
            }

            post.setLikes(likesJob2->likeInfo());
        });

        likesJob->start();
    }

    if (d->options & PostInfo::FetchAllComments || d->options & PostInfo::FetchCommentsCountOnly) {
        // start comments job for the post id, keep a map
    }*/
}

#include "postjob.moc"
