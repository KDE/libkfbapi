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
#include "postinfoparser_p.h"
#include "facebookjobs_p.h"

#include <qjson/qobjecthelper.h>

using namespace KFbAPI;

class KFbAPI::PostJobPrivate : public KFbAPI::FacebookGetJobPrivate {
public:
    QList<PostInfo> postInfo;
};

//-----------------------------------------------------------------------------

PostJob::PostJob(const QString &postId, const QString &accessToken, QObject *parent)
    : FacebookGetIdJob(*new PostJobPrivate, postId, accessToken, parent)
{
}

PostJob::PostJob(const QStringList &postIds, const QString &accessToken, QObject *parent)
    : FacebookGetIdJob(*new PostJobPrivate, postIds, accessToken, parent)
{
}

QList<PostInfo> PostJob::postInfo() const
{
    Q_D(const PostJob);
    return d->postInfo;
}

void PostJob::handleSingleData(const QVariant &data)
{
    Q_D(PostJob);
    PostInfoParser parser;
    const QVariantMap dataMap = data.toMap();
    QJson::QObjectHelper::qvariant2qobject(dataMap, &parser);
    d->postInfo.append(parser.dataObject());
}

#include "postjob.moc"
