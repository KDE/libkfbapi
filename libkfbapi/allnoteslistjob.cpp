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

#include <QDebug>
#include <QUrl>
#include <QUrlQuery>

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

bool AllNotesListJob::shouldStartNewJob(const QUrl &prev, const QUrl &next)
{
    Q_UNUSED(next);
    Q_D(AllNotesListJob);
    QUrlQuery query(prev);
    const QString since = query.queryItemValue(QStringLiteral("since"));
    if (since.isEmpty()) {
        qDebug() << "Aborting notes fetching, no date range found in URL!";
        return false;
    }
    QDateTime sinceTime;
    sinceTime.setTime_t(since.toLongLong());
    if (!sinceTime.isValid()) {
        qDebug() << "Aborting notes fetching, invalid date range found in URL!";
        return false;
    }

    return (sinceTime >= d->lowerLimit);
}

ListJobBase* AllNotesListJob::createJob(const QUrl &prev, const QUrl &next)
{
    Q_UNUSED(next);
    Q_D(AllNotesListJob);
    QUrlQuery query(prev);
    NotesListJob * const job = new NotesListJob(d->accessToken);
    if (!prev.isEmpty()) {
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
