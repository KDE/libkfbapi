 /* Copyright 2012 Pankaj Bhambhani <pankajb64@gmail.com>

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

namespace KFbAPI
{

class GetLikesJobPrivate;

class LIBKFBAPI_EXPORT GetLikesJob : public FacebookGetJob
{
    Q_OBJECT

public:
    GetLikesJob(const QString &postId, const QString &accessToken, QObject *parent = 0);

    uint likeCount() const;
    bool userLikes() const;
    bool canLike() const;
    QString href() const;

protected:
    void handleData(const QVariant& data);

private:
    Q_DECLARE_PRIVATE(GetLikesJob);
};

}

#endif
