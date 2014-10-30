/* Copyright 2011 Thomas McGuire <mcguire@kde.org>
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

#include "pagedlistjob.h"
#include "pagedlistjob_p.h"

#include "listjobbase.h"

#include <QDebug>

using namespace KFbAPI;

PagedListJob::PagedListJob(const QString &accessToken, QObject *parent)
    : KJob(parent),
      d_ptr(new PagedListJobPrivate)
{
    Q_D(PagedListJob);
    d->accessToken = accessToken; 
}

PagedListJob::PagedListJob(PagedListJobPrivate &dd, const QString &accessToken, QObject *parent)
    : KJob(parent),
      d_ptr(&dd)
{
    Q_D(PagedListJob);
    d->accessToken = accessToken;
}

PagedListJob::~PagedListJob()
{
    delete d_ptr;
}

bool PagedListJob::doKill()
{
    Q_D(PagedListJob);

    if (d->currentJob) {
        d->currentJob->kill(KJob::Quietly);
    }

    return KJob::doKill();
}

void PagedListJob::setLowerLimit(const QDateTime &lowerLimit)
{
    Q_D(PagedListJob);
    d->lowerLimit = lowerLimit;
}

void PagedListJob::start()
{
    Q_D(PagedListJob);

    Q_ASSERT(d->lowerLimit.isValid());
    Q_ASSERT(!d->currentJob);

    d->currentJob = createJob(QUrl(), QUrl());

    connect(d->currentJob, SIGNAL(result(KJob*)),
            this, SLOT(listJobFinished(KJob*)));

    d->currentJob->start();
}

void PagedListJob::listJobFinished(KJob *job)
{
    Q_D(PagedListJob);

    Q_ASSERT(job == d->currentJob);
    ListJobBase * const listJob = dynamic_cast<ListJobBase*>(job);
    Q_ASSERT(listJob);
    if (job->error()) {
        d->currentJob = 0;
        setError(listJob->error());
        setErrorText(listJob->errorString());
        emitResult();
    } else {
        qDebug() << "Got" << listJob->entriesCount() << "items from our subjob.";

        const QUrl next = QUrl::fromUserInput(listJob->nextItems());
        const QUrl prev = QUrl::fromUserInput(listJob->previousItems());

        // Stop when we got all items after a certain dates, or no items at all
        if (listJob->entriesCount() == 0 || !shouldStartNewJob(prev, next)) {
            qDebug() << "All items fetched.";
            d->currentJob = 0;
            emitResult();
        } else {
            appendItems(d->currentJob);

            d->currentJob = createJob(prev, next);
            connect(d->currentJob, SIGNAL(result(KJob*)),
                    this, SLOT(listJobFinished(KJob*)));

            d->currentJob->start();
        }
    }
}
