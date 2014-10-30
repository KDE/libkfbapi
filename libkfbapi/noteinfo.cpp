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

#include "noteinfo.h"

using namespace KFbAPI;

class NoteInfo::NoteInfoPrivate : public QSharedData {
public:
    QJsonObject jsonData;
};

NoteInfo::NoteInfo(const QJsonObject &jsonData)
    : d(new NoteInfoPrivate)
{
    d->jsonData = jsonData;
}

NoteInfo::NoteInfo()
    : d(new NoteInfoPrivate)
{
}

NoteInfo::NoteInfo(const NoteInfo &other)
{
    d = other.d;
}

NoteInfo::~NoteInfo()
{
}

NoteInfo& NoteInfo::operator=(const NoteInfo &other)
{
    if (this == &other) return *this; //Protect against self-assignment
    d = other.d;
    return *this;
}

// KMime::Message::Ptr NoteInfo::asNote() const
// {
//     KMime::Message * const note = new KMime::Message();
//
//     QString m = "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n";
//     m += "<html><head></head><body>\n";
//     m += message();
//     m += "</body>";
//
//     note->contentType()->setMimeType("text/html");
//     note->contentType()->setCharset("utf-8");
//     note->fromUnicodeString(m);
//     note->date()->fromUnicodeString(updatedTime().toString(KDateTime::RFCDateDay), "utf-8");
//     note->subject()->fromUnicodeString(subject(), "utf-8");
//     note->from()->fromUnicodeString("you@facebook", "utf-8");
//     note->contentTransferEncoding()->setEncoding(KMime::Headers::CEquPr);
//
//     note->assemble();
//
//     return KMime::Message::Ptr(note);
// }

QString NoteInfo::id() const
{
    return d->jsonData.value(QStringLiteral("id")).toString();
}

QString NoteInfo::from() const
{
    return d->jsonData.value(QStringLiteral("from")).toString();
}

QString NoteInfo::subject() const
{
    return d->jsonData.value(QStringLiteral("subject")).toString();
}

QString NoteInfo::message() const
{
    return d->jsonData.value(QStringLiteral("message")).toString();
}

QString NoteInfo::createdTimeString() const
{
    return d->jsonData.value(QStringLiteral("created_time")).toString();
}

QDateTime NoteInfo::createdTime() const
{
    return QDateTime::fromString(d->jsonData.value(QStringLiteral("id")).toString(), Qt::ISODate);
}

QString NoteInfo::updatedTimeString() const
{
    return d->jsonData.value(QStringLiteral("updated_time")).toString();
}

QDateTime NoteInfo::updatedTime() const
{
    return QDateTime::fromString(d->jsonData.value(QStringLiteral("updated_time")).toString(), Qt::ISODate);
}
