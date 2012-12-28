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

#include "alleventslistjob.h"
#include "pagedlistjob_p.h"

#include "eventslistjob.h"

#include <KDebug>

using namespace KFbAPI;

class KFbAPI::AllEventsListJobPrivate : public KFbAPI::PagedListJobPrivate {
public:
    QList<EventInfo> events;
};

//-----------------------------------------------------------------------------

AllEventsListJob::AllEventsListJob(const QString &accessToken, QObject *parent)
  : PagedListJob(*new AllEventsListJobPrivate, accessToken, parent)
{
}

QList<EventInfo> AllEventsListJob::allEvents() const
{
    Q_D(const AllEventsListJob);
    return d->events;
}

void AllEventsListJob::appendItems(const ListJobBase *job)
{
    Q_D(AllEventsListJob);
    const EventsListJob * const listJob = dynamic_cast<const EventsListJob*>(job);
    Q_ASSERT(listJob);
    d->events.append(listJob->events());
}

bool AllEventsListJob::shouldStartNewJob(const KUrl &prev, const KUrl &next)
{
    Q_UNUSED(prev);
    Q_D(AllEventsListJob);
    const QString until = next.queryItem("until");
    if (until.isEmpty()) {
        kDebug() << "Aborting events fetching, no date range found in URL!";
        return false;
    }
    KDateTime untilTime;
    untilTime.setTime_t(until.toLongLong());
    if (!untilTime.isValid()) {
        kDebug() << "Aborting events fetching, invalid date range found in URL!";
        return false;
    }

    return (untilTime >= d->lowerLimit);
}

ListJobBase* AllEventsListJob::createJob(const KUrl &prev, const KUrl &next)
{
    Q_UNUSED(prev);
    Q_D(AllEventsListJob);
    EventsListJob * const job = new EventsListJob(d->accessToken);
    if (!next.isEmpty()) {
        const QString limit = next.queryItem("limit");
        const QString until = next.queryItem("until");
        const QString since = next.queryItem("since");
        if (!limit.isEmpty()) {
            job->addQueryItem("limit", limit);
        }
        if (!until.isEmpty()) {
            job->addQueryItem("until", until);
        }
        if (!since.isEmpty()) {
            job->addQueryItem("since", since);
        }
    }

    return job;
}
