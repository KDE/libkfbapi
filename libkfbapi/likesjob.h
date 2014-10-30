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

#ifndef KFBAPI_GETLIKESJOB_H
#define KFBAPI_GETLIKESJOB_H

#include "facebookjobs.h"
#include "postinfo.h"
#include "likeinfo.h"

namespace KFbAPI
{

class LikesJobPrivate;

class LIBKFBAPI_EXPORT LikesJob : public FacebookGetJob
{
    Q_OBJECT

public:
    LikesJob(const QString &postId, const PostInfo::PostFetchOptions &options, const QString &accessToken, QObject *parent = 0);

    LikeInfo likeInfo() const;

protected:
    void handleData(const QJsonDocument &data);

private:
    Q_DECLARE_PRIVATE(LikesJob);
};

}

#endif
