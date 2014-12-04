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

#ifndef KFBAPI_EVENTINFO_H
#define KFBAPI_EVENTINFO_H

#include "libkfbapi_export.h"

#include <QDateTime>
#include <QJsonObject>
#include <QSharedPointer>

// #include <KCalCore/Event>
// #include <KCalCore/Attendee>

namespace KFbAPI {

// typedef KCalCore::Event Event;
// typedef KCalCore::Attendee Attendee;
// typedef KCalCore::Event::Ptr EventPtr;
// typedef KCalCore::Incidence::Ptr IncidencePtr;
// typedef KCalCore::Attendee::Ptr AttendeePtr;

/**
* An attendee to an event
*/
class LIBKFBAPI_EXPORT AttendeeInfo
{
public:

    /**
    * @brief Construct an attendee to an event.
    *
    * @param name The name of the attendee.
    * @param id The facebook id of the attendee.
    * @param status The RSVP status of the attendee.
    */
    AttendeeInfo(const QString &name, const QString &id, const QString &status);
    AttendeeInfo(const AttendeeInfo &other);
    ~AttendeeInfo();

    AttendeeInfo &operator=(const AttendeeInfo &other);

    /**
    * @return The name of the attendee.
    */
    QString name() const;

    /**
    * @return Returns the facebook id of the attendee.
    */
    QString id() const;

    /**
    * @return Returns the RSVP state of the attendee.
    */
    QString status() const;

private:
    class AttendeeInfoPrivate;
    QSharedDataPointer<AttendeeInfoPrivate> d;
};

typedef QSharedPointer<AttendeeInfo> AttendeeInfoPtr;


/**
* Class to describe a facebook event.
*/
class LIBKFBAPI_EXPORT EventInfo
{
public:
    EventInfo(const QJsonObject &jsonData);
    EventInfo();
    EventInfo(const EventInfo &other);
    ~EventInfo();

    EventInfo &operator=(const EventInfo &other);

    /**
    * @return The name of the event.
    */
    QString name() const;

    /**
    * @return The start time of the event as a QString in the "facebook format".
    */
    QString startTimeString() const;

    /**
    * @return The start time of the event as a QDateTime.
    */
    QDateTime startTime() const;

    /**
    * @return The end time of the event as a QString in the "facebook format".
    */
    QString endTimeString() const;

    /**
    * @return The end time of the event as a QDateTime.
    */
    QDateTime endTime() const;

    /**
    * @return The location of the event
    */
    QString location() const;

    /**
    * @return The facebook id of the event.
    */
    QString id() const;

    /**
    * @return The description of the event.
    */
    QString description() const;

    /**
    * @return The organizer of the event as a QString.
    */
    QString organizer() const;

    /**
    * @return The time of the last update of the event in "facebook format".
    */
    QString updatedTimeString() const;

    /**
    * @return The time of the last update of the event as a QDateTime.
    */
    QDateTime updatedTime() const;

    /**
    * @brief Add a list of attendee objects to this event.
    * @param attendees A list of attendee objects of people that have responded
    *                  or are requested to respond to this event.
    */
//     void addAttendees(const QList<AttendeeInfoPtr> &attendees);
    QList<AttendeeInfoPtr> attendees() const;

//     EventPtr asEvent() const;

private:
    class EventInfoPrivate;
    QSharedDataPointer<EventInfoPrivate> d;
};

}

#endif
