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

#ifndef KFBAPI_ALLEVENTSLISTJOB_H
#define KFBAPI_ALLEVENTSLISTJOB_H

#include "pagedlistjob.h"
#include "eventinfo.h"
#include "libkfbapi_export.h"

namespace KFbAPI {

class LIBKFBAPI_EXPORT AllEventsListJob : public PagedListJob
{
    Q_OBJECT
public:
    explicit AllEventsListJob(const QString &accessToken, QObject *parent = 0);
    QList< EventInfoPtr > allEvents() const;

protected:
    virtual void appendItems(const ListJobBase *job);
    virtual ListJobBase* createJob(const KUrl &prev, const KUrl &next);
    virtual bool shouldStartNewJob(const KUrl &prev, const KUrl &next);

private:
    QList<EventInfoPtr> m_events;
};

}

#endif
