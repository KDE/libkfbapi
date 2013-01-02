 /* Copyright 2012 Pankaj Bhambhani <pankajb64@gmail.com>

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

#include "getlikesjob.h"
#include "facebookjobs_p.h"

using namespace KFbAPI;

class KFbAPI::GetLikesJobPrivate : public KFbAPI::FacebookGetJobPrivate {
public:
    QString postId;
    QString href;
    uint likeCount;
    bool userLikes;
    bool canLike;
};

GetLikesJob::GetLikesJob(const QString &postId, const QString &accessToken, QObject *parent)
    : FacebookGetJob(*new GetLikesJobPrivate, "/fql", accessToken, parent)
{
    Q_D(GetLikesJob);
    d->likeCount = 0;
    d->userLikes = false;
    d->canLike = true;
    d->postId = postId;
    QString query = QString("SELECT likes FROM stream WHERE post_id = \"%1\"").arg(d->postId);
    addQueryItem("q", query);
}

void GetLikesJob::handleData(const QVariant &data)
{
    Q_D(GetLikesJob);
    QVariantMap dataMap = data.toMap();

    if (!dataMap.isEmpty()) {
        QVariantList dataList = dataMap["data"].toList();

        if (!dataList.isEmpty()) {
            QVariantMap map = dataList[0].toMap();

            if (!map.isEmpty()) {
                QVariantMap likeMap = map["likes"].toMap();

                if (!likeMap.isEmpty()) {
                    d->likeCount = likeMap["count"].toUInt();
                    d->userLikes = likeMap["user_likes"].toBool();
                    d->canLike = likeMap["can_like"].toBool();
                    d->href = likeMap["href"].toString();
                }
            }
        }
    }
}

uint GetLikesJob::likeCount() const
{
    Q_D(const GetLikesJob);
    return d->likeCount;
}

bool GetLikesJob::userLikes() const
{
    Q_D(const GetLikesJob);
    return d->userLikes;
}

bool GetLikesJob::canLike() const
{
    Q_D(const GetLikesJob);
    return d->canLike;
}

QString GetLikesJob::href() const
{
    Q_D(const GetLikesJob);
    return d->href;
}
