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
#include "noteslistjob.h"
#include "noteinfoparser_p.h"

#include <KDebug>
#include <qjson/qobjecthelper.h>

using namespace KFbAPI;

NotesListJob::NotesListJob(const QString &accessToken, QObject *parent)
    : ListJobBase("/me/notes", accessToken, true, parent)
{
}

QList<NoteInfo> NotesListJob::notes() const
{
    return m_notes;
}

void NotesListJob::handleItem(const QVariant &item)
{
    NoteInfoParser parser;
    QJson::QObjectHelper::qvariant2qobject(item.toMap(), &parser);
    m_notes.append(parser.dataObject());
}

int NotesListJob::entriesCount() const
{
    return m_notes.size();
}
