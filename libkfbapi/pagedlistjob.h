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

#ifndef KFBAPI_PAGEDLISTJOB_H
#define KFBAPI_PAGEDLISTJOB_H

#include "libkfbapi_export.h"

#include <KJob>
#include <KUrl>
#include <KDateTime>

#include <QPointer>

namespace KFbAPI {

class ListJobBase;
class PagedListJobPrivate;

class LIBKFBAPI_EXPORT PagedListJob : public KJob
{
    Q_OBJECT
public:
    explicit PagedListJob(const QString &accessToken, QObject *parent = 0);
    virtual ~PagedListJob();

    void setLowerLimit(const KDateTime &lowerLimit);
    virtual void start();

protected Q_SLOTS:
    void listJobFinished(KJob *job);

protected:
    virtual bool doKill();
    virtual ListJobBase* createJob(const KUrl &prev, const KUrl &next) = 0;
    virtual void appendItems(const ListJobBase *job) = 0;
    virtual bool shouldStartNewJob(const KUrl &prev, const KUrl &next) = 0;

    PagedListJob(PagedListJobPrivate &dd, const QString &accessToken, QObject *parent = 0);

    PagedListJobPrivate * const d_ptr;

private:
    Q_DISABLE_COPY(PagedListJob)
    Q_DECLARE_PRIVATE(PagedListJob)
};

}

#endif
