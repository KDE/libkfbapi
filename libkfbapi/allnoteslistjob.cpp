/* Copyright 2011 Roeland Jago Douma <unix@rullzer.com>

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

#include "allnoteslistjob.h"
#include "noteslistjob.h"
#include "pagedlistjob_p.h"

#include <KDebug>
#include <KUrl>

using namespace KFbAPI;

class KFbAPI::AllNotesListJobPrivate : public KFbAPI::PagedListJobPrivate {
public:
    QList<NoteInfo> notes;
};

//-----------------------------------------------------------------------------

AllNotesListJob::AllNotesListJob(const QString &accessToken, QObject *parent)
  : PagedListJob(*new AllNotesListJobPrivate, accessToken, parent)
{
}

QList<NoteInfo> AllNotesListJob::allNotes() const
{
    Q_D(const AllNotesListJob);
    return d->notes;
}

void AllNotesListJob::appendItems(const ListJobBase* job)
{
    Q_D(AllNotesListJob);
    const NotesListJob * const listJob = dynamic_cast<const NotesListJob*>(job);
    Q_ASSERT(listJob);
    d->notes.append(listJob->notes());
}

bool AllNotesListJob::shouldStartNewJob(const KUrl &prev, const KUrl &next)
{
    Q_UNUSED(next);
    Q_D(AllNotesListJob);
    const QString since = prev.queryItem("since");
    if (since.isEmpty()) {
        kDebug() << "Aborting notes fetching, no date range found in URL!";
        return false;
    }
    KDateTime sinceTime;
    sinceTime.setTime_t(since.toLongLong());
    if (!sinceTime.isValid()) {
        kDebug() << "Aborting notes fetching, invalid date range found in URL!";
        return false;
    }

    return (sinceTime >= d->lowerLimit);
}

ListJobBase* AllNotesListJob::createJob(const KUrl &prev, const KUrl &next)
{
    Q_UNUSED(next);
    Q_D(AllNotesListJob);
    NotesListJob * const job = new NotesListJob(d->accessToken);
    if (!prev.isEmpty()) {
        const QString limit = prev.queryItem("limit");
        const QString until = prev.queryItem("until");
        const QString since = prev.queryItem("since");
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
