 /* Copyright (c) 2014 Martin Klapetek <mklapetek@kde.org>

   This library is free software; you can redistribute it and/or modify
   it under the terms of the GNU Library General Public License as published
   by the Free Software Foundation; either version 2 of the License or
   ( at your option ) version 3 or, at the discretion of KDE e.V.
   ( which shall act as a proxy as in section 14 of the GPLv3 ), any later version.

   This library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Library General Public License for more details.

   You should have received a copy of the GNU Library General Public License
   along with this library; see the file COPYING.LIB.  If not, write to
   the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.
*/

#include "commentsjob.h"
#include "facebookjobs_p.h"
#include "likeinfo.h"

#include <QDebug>

using namespace KFbAPI;

class KFbAPI::CommentsJobPrivate : public KFbAPI::FacebookGetJobPrivate {
public:
    QJsonDocument jsonData;
    CommentInfo comments;
    PostInfo::PostFetchOptions options;
};

CommentsJob::CommentsJob(const QString &postId, const PostInfo::PostFetchOptions &options, const QString &accessToken, QObject *parent)
    : FacebookGetJob(*new CommentsJobPrivate, QStringLiteral("/") + postId + QStringLiteral("/comments"), accessToken, parent)
{
    Q_D(CommentsJob);

    d->options = options;

    if (options & PostInfo::FetchCommentsCountOnly) {
        // limit the actual comment data to 1 so we don't waste
        // bandwith when only counts were requested
        addQueryItem(QStringLiteral("limit"), QStringLiteral("1"));
    }

    addQueryItem(QStringLiteral("summary"), QStringLiteral("1"));
}

void CommentsJob::handleData(const QJsonDocument &data)
{
    Q_D(CommentsJob);

    d->jsonData = data;

//     if (d->options & PostInfo::FetchLikesCountOnly) {
        d->comments = CommentInfo(data.object());
//     } else {
        //TODO needs paging support
//     }
}

CommentInfo CommentsJob::commentInfo() const
{
    Q_D(const CommentsJob);
    return d->comments;
}
