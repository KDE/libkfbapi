/* Copyright 2012 Martin Klapetek <mklapetek@kde.org>

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

#ifndef KFBAPI_FACEBOOKJOBS_P_H
#define KFBAPI_FACEBOOKJOBS_P_H

#include <KUrl>

#include <QPointer>

class KJob;
class QStringList;

namespace KFbAPI {

class FacebookJobPrivate {
public:
    void init(const QString &path, const QString &accessToken) 
    {
        Q_ASSERT(path.startsWith('/'));
        url.setProtocol("https");
        url.setHost("graph.facebook.com");
        url.setPath(path);
        url.addQueryItem("access_token", accessToken);
    }

    virtual ~FacebookJobPrivate() {}

    KUrl url;
    QPointer<KJob> job;          /** Pointer to the running job */
};

//-----------------------------------------------------------------------------

class FacebookGetJobPrivate : public FacebookJobPrivate {
public:
    virtual ~FacebookGetJobPrivate() {}

    QStringList fields; /** The field to retrieve from facebook */
    QStringList ids;    /** The id's to retrieve from facebook */
    bool multiQuery;
};

}

#endif
