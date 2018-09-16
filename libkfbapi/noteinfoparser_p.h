/* Copyright 2012 Martin Klapetek <mklapetek@kde.org>

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

#ifndef KFBAPI_NOTEINFOPARSER_P_H
#define KFBAPI_NOTEINFOPARSER_P_H

#include "noteinfo.h"

#include <QObject>

namespace KFbAPI {

class NoteInfoParser : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString id WRITE setId READ id)
    Q_PROPERTY(QString from WRITE setFrom READ from)
    Q_PROPERTY(QString subject WRITE setSubject READ subject)
    Q_PROPERTY(QString message WRITE setMessage READ message)
    Q_PROPERTY(QString created_time WRITE setCreatedTimeString READ createdTimeString)
    Q_PROPERTY(QString updated_time WRITE setUpdatedTimeString READ updatedTimeString)

public:
    void setDataObject(const NoteInfo &noteInfo) {m_noteInfo = noteInfo;}
    NoteInfo dataObject() const {return m_noteInfo;}

    void setId(const QString &id) {m_noteInfo.setId(id);}
    QString id() const {return m_noteInfo.id();}

    void setFrom(const QString &from) {m_noteInfo.setFrom(from);}
    QString from() const {return m_noteInfo.from();}

    void setSubject(const QString &subject) {m_noteInfo.setSubject(subject);}
    QString subject() const {return m_noteInfo.subject();}

    void setMessage(const QString &message) {m_noteInfo.setMessage(message);}
    QString message() const {return m_noteInfo.message();}

    void setCreatedTimeString(const QString &createdTimeString) {m_noteInfo.setCreatedTimeString(createdTimeString);}
    QString createdTimeString() const {return m_noteInfo.createdTimeString();}

    void setUpdatedTimeString(const QString &updatedTimeString) {m_noteInfo.setUpdatedTimeString(updatedTimeString);}
    QString updatedTimeString() const {return m_noteInfo.updatedTimeString();}

private:
    NoteInfo m_noteInfo;
};

}

#endif
