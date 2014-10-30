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
#include "eventslistjob.h"
#include "pagedlistjob_p.h"

#include <QDebug>
#include <QUrlQuery>

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

bool AllEventsListJob::shouldStartNewJob(const QUrl &prev, const QUrl &next)
{
    Q_UNUSED(prev);
    Q_D(AllEventsListJob);
    QUrlQuery query(next);
    const QString until = query.queryItemValue(QStringLiteral("until"));
    if (until.isEmpty()) {
        qDebug() << "Aborting events fetching, no date range found in URL!";
        return false;
    }
    QDateTime untilTime;
    untilTime.setTime_t(until.toLongLong());
    if (!untilTime.isValid()) {
        qDebug() << "Aborting events fetching, invalid date range found in URL!";
        return false;
    }

    return (untilTime >= d->lowerLimit);
}

ListJobBase* AllEventsListJob::createJob(const QUrl &prev, const QUrl &next)
{
    Q_UNUSED(prev);
    Q_D(AllEventsListJob);
    QUrlQuery query(next);
    EventsListJob * const job = new EventsListJob(d->accessToken);
    if (!next.isEmpty()) {
        const QString limit = query.queryItemValue(QStringLiteral("limit"));
        const QString until = query.queryItemValue(QStringLiteral("until"));
        const QString since = query.queryItemValue(QStringLiteral("since"));
        if (!limit.isEmpty()) {
            job->addQueryItem(QStringLiteral("limit"), limit);
        }
        if (!until.isEmpty()) {
            job->addQueryItem(QStringLiteral("until"), until);
        }
        if (!since.isEmpty()) {
            job->addQueryItem(QStringLiteral("since"), since);
        }
    }

    return job;
}
