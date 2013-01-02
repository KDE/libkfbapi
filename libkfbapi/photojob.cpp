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

#include "photojob.h"
#include "facebookjobs_p.h"

#include <KDebug>
#include <KIO/Job>

using namespace KFbAPI;

class KFbAPI::PhotoJobPrivate : public KFbAPI::FacebookGetJobPrivate {
public:
    QImage image;
};

//-----------------------------------------------------------------------------

PhotoJob::PhotoJob(const QString &friendId, const QString &accessToken, QObject *parent)
    : FacebookGetJob(*new PhotoJobPrivate, "/" + friendId + "/picture", accessToken, parent)
{
    addQueryItem("type", "large");
}

QImage PhotoJob::photo() const
{
    Q_D(const PhotoJob);
    return d->image;
}

void PhotoJob::jobFinished(KJob *job)
{
    Q_D(PhotoJob);
    KIO::StoredTransferJob * const transferJob = dynamic_cast<KIO::StoredTransferJob *>(job);
    Q_ASSERT(transferJob);
    if (transferJob->error()) {
        setError(transferJob->error());
        setErrorText(KIO::buildErrorString(error(), transferJob->errorText()));
        kWarning() << "Job error: " << transferJob->errorText();
    } else {
        kDebug() << "Got picture of" << transferJob->data().length() << "bytes.";
        d->image = QImage::fromData(transferJob->data());
    }

    emitResult();
    d->job = 0;
}

void PhotoJob::handleData(const QVariant &data)
{
    Q_UNUSED(data);
}

#include "photojob.moc"
