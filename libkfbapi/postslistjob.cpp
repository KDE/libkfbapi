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

#include "postslistjob.h"
#include "postinfoparser_p.h"

#include <qjson/qobjecthelper.h>

using namespace KFbAPI;

class KFbAPI::PostsListJobPrivate {
public:
    QList<PostInfo> posts;
};

//-----------------------------------------------------------------------------

PostsListJob::PostsListJob(const QString &accessToken, QObject *parent)
  : ListJobBase("/me/home", accessToken, true, parent),
    d_ptr(new PostsListJobPrivate)
{
}

PostsListJob::PostsListJob(const QString &userId, const QString &accessToken, QObject *parent)
    : ListJobBase("/" + userId + "/feed", accessToken, true, parent),
      d_ptr(new PostsListJobPrivate)
{
}

PostsListJob::~PostsListJob()
{
    delete d_ptr;
}

QList<PostInfo> PostsListJob::posts() const
{
    Q_D(const PostsListJob);
    return d->posts;
}

void PostsListJob::handleItem(const QVariant &item)
{
    Q_D(PostsListJob);
    PostInfoParser parser;
    QJson::QObjectHelper::qvariant2qobject(item.toMap(), &parser);
    d->posts.append(parser.dataObject());
}

int PostsListJob::entriesCount() const
{
    Q_D(const PostsListJob);
    return d->posts.size();
}

