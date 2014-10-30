 /* Copyright 2012 Pankaj Bhambhani <pankajb64@gmail.com>
    Copyright (c) 2014 Martin Klapetek <mklapetek@kde.org>

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

#include "likesjob.h"
#include "facebookjobs_p.h"
#include "likeinfo.h"

#include <QDebug>

using namespace KFbAPI;

class KFbAPI::LikesJobPrivate : public KFbAPI::FacebookGetJobPrivate {
public:
    QJsonDocument jsonData;
    LikeInfo likes;
    PostInfo::PostFetchOptions options;
};

LikesJob::LikesJob(const QString &postId, const PostInfo::PostFetchOptions &options, const QString &accessToken, QObject *parent)
    : FacebookGetJob(*new LikesJobPrivate, QStringLiteral("/") + postId + QStringLiteral("/likes"), accessToken, parent)
{
    Q_D(LikesJob);

    d->options = options;

    if (options & PostInfo::FetchLikesCountOnly) {
        // limit the actual like data to 1 so we don't waste
        // bandwith when only counts were requested
        addQueryItem(QStringLiteral("limit"), QStringLiteral("1"));
    }

    addQueryItem(QStringLiteral("summary"), QStringLiteral("1"));
}

void LikesJob::handleData(const QJsonDocument &data)
{
    Q_D(LikesJob);

    qDebug() << data.toJson();

    d->jsonData = data;

//     if (d->options & PostInfo::FetchLikesCountOnly) {
        d->likes = LikeInfo(data.object());
//     } else {
        //TODO needs paging support
//     }
}

LikeInfo LikesJob::likeInfo() const
{
    Q_D(const LikesJob);
    return d->likes;
}
