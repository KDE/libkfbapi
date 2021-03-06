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

#include "notejob.h"
#include "noteinfoparser_p.h"
#include "facebookjobs_p.h"

#include <KDebug>

#include <qjson/qobjecthelper.h>

using namespace KFbAPI;

class KFbAPI::NoteJobPrivate : public KFbAPI::FacebookGetJobPrivate {
public:
    QList<NoteInfo> noteInfo;
};

//-----------------------------------------------------------------------------

NoteJob::NoteJob(const QString &noteId, const QString &accessToken, QObject *parent)
    : FacebookGetIdJob(*new NoteJobPrivate, noteId, accessToken, parent)
{
}

NoteJob::NoteJob(const QStringList &noteIds, const QString &accessToken, QObject *parent)
    : FacebookGetIdJob(*new NoteJobPrivate, noteIds, accessToken, parent)
{
}

QList<NoteInfo> NoteJob::noteInfo() const
{
    Q_D(const NoteJob);
    return d->noteInfo;
}

void NoteJob::handleSingleData(const QVariant &data)
{
    Q_D(NoteJob);
    NoteInfoParser parser;
    const QVariantMap dataMap = data.toMap();
    QJson::QObjectHelper::qvariant2qobject(dataMap, &parser);
    d->noteInfo.append(parser.dataObject());
}

#include "notejob.moc"
