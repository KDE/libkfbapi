/* Copyright 2011 Thomas McGuire <mcguire@kde.org>

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

#ifndef KFBAPI_LISTJOBBASE_H
#define KFBAPI_LISTJOBBASE_H

#include "libkfbapi_export.h"

#include "facebookjobs.h"

namespace KFbAPI {

class ListJobBasePrivate;

class LIBKFBAPI_EXPORT ListJobBase : public FacebookGetJob
{
    Q_OBJECT
public:
    ListJobBase(const QString &path, const QString &accessToken, bool multiResult = true, QObject *parent = 0);
    virtual ~ListJobBase();
    virtual int entriesCount() const = 0;

    QString previousItems() const;
    QString nextItems() const;

protected:
    virtual void handleData(const QVariant &data);
    virtual void handleItems(const QVariant &data);
    virtual void handleItem(const QVariant &item) = 0;

private:
    Q_DECLARE_PRIVATE(ListJobBase)
};

}

#endif
