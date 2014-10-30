/*
    Copyright (C) 2012  Martin Klapetek <martin.klapetek@gmail.com>

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


#include "allpostslistjob.h"
#include "postslistjob.h"
#include "pagedlistjob_p.h"
#include "postcompositejob.h"

#include <QDebug>
#include <QUrlQuery>

using namespace KFbAPI;

class KFbAPI::AllPostsListJobPrivate : public KFbAPI::PagedListJobPrivate {
public:
    QList<PostInfo> posts;
    PostInfo::PostFetchOptions options;
};

//-----------------------------------------------------------------------------

AllPostsListJob::AllPostsListJob(const PostInfo::PostFetchOptions &options, const QString &accessToken, QObject *parent)
    : PagedListJob(*new AllPostsListJobPrivate, accessToken, parent)
{
    Q_D(AllPostsListJob);
    d->options = options;
}

QList<PostInfo> AllPostsListJob::allPosts() const
{
    Q_D(const AllPostsListJob);
    return d->posts;
}

void AllPostsListJob::appendItems(const ListJobBase *job)
{
    Q_D(AllPostsListJob);
    const PostsListJob * const listJob = dynamic_cast<const PostsListJob*>(job);
    Q_ASSERT(listJob);
    d->posts.append(listJob->posts());
}

bool AllPostsListJob::shouldStartNewJob(const QUrl &prev, const QUrl &next)
{
    Q_UNUSED(prev);
    Q_D(AllPostsListJob);
    QUrlQuery query(next);
    const QString until = query.queryItemValue(QStringLiteral("until"));
    if (until.isEmpty()) {
        qDebug() << "Aborting posts fetching, no date range found in URL!";
        return false;
    }
    QDateTime untilTime;
    untilTime.setTime_t(until.toLongLong());
    if (!untilTime.isValid()) {
        qDebug() << "Aborting posts fetching, invalid date range found in URL!";
        return false;
    }
    return (untilTime >= d->lowerLimit);
}

ListJobBase* AllPostsListJob::createJob(const QUrl &prev, const QUrl &next)
{
    Q_UNUSED(prev);
    Q_D(AllPostsListJob);
//     PostCompositeJob * const job = new PostCompositeJob(QString(), d->options, d->accessToken, this);
    PostsListJob * const job = new PostsListJob(d->accessToken);
    if (!next.isEmpty()) {
        QUrlQuery query(next);
        const QString limit = query.queryItemValue(QStringLiteral("limit"));
        const QString until = query.queryItemValue(QStringLiteral("until"));
        const QString since = query.queryItemValue(QStringLiteral("since"));
        if (!limit.isEmpty()) {
            job->addQueryItem(QStringLiteral("limit"), limit);
        }
        if (!until.isEmpty()) {
            job->addQueryItem(QStringLiteral("until"), until);
        }
        if (!since.isEmpty()) {
            job->addQueryItem(QStringLiteral("since"), since);
        }
    } else {
        //add default values for the first job
        job->addQueryItem(QStringLiteral("since"), d->lowerLimit.toString());
        job->addQueryItem(QStringLiteral("limit"), QString::number(100));
    }
    return job;
}
