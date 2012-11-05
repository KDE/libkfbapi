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

#ifndef KFBAPI_EVENTINFOPARSER_H
#define KFBAPI_EVENTINFOPARSER_H

#include "eventinfo.h"

#include <QObject>

namespace KFbAPI {

class EventInfoParser : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString name WRITE setName READ name)
    Q_PROPERTY(QString start_time WRITE setStartTimeString READ startTimeString)
    Q_PROPERTY(QString end_time WRITE setEndTimeString READ endTimeString)
    Q_PROPERTY(QString location WRITE setLocation READ location)
    Q_PROPERTY(QString id WRITE setId READ id)
    Q_PROPERTY(QString description WRITE setDescription READ description)
    Q_PROPERTY(QString updated_time WRITE setUpdatedTimeString READ updatedTimeString)

public:
    void setDataObject(const EventInfo &eventInfo) {m_eventInfo = eventInfo;}
    EventInfo dataObject() const {return m_eventInfo;}

    void setName(const QString &name) {m_eventInfo.setName(name);}
    QString name() const {return m_eventInfo.name();}

    void setStartTimeString(const QString &startTimeString) {m_eventInfo.setStartTimeString(startTimeString);}
    QString startTimeString() const {return m_eventInfo.startTimeString();}

    void setEndTimeString(const QString &endTimeString) {m_eventInfo.setEndTimeString(endTimeString);}
    QString endTimeString() const {return m_eventInfo.endTimeString();}

    void setLocation(const QString &location) {m_eventInfo.setLocation(location);}
    QString location() const {return m_eventInfo.location();}

    void setId(const QString &id) {m_eventInfo.setId(id);}
    QString id() const {return m_eventInfo.id();}

    void setDescription(const QString &description) {m_eventInfo.setDescription(description);}
    QString description() const {return m_eventInfo.description();}

    void setUpdatedTimeString(const QString &updatedTimeString) {m_eventInfo.setUpdatedTimeString(updatedTimeString);}
    QString updatedTimeString() const {return m_eventInfo.updatedTimeString();}

private:
    EventInfo m_eventInfo;
};

}

#endif
