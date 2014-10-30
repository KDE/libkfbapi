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

#include "eventinfo.h"

// #include "util.h"

#include <QDebug>
// #include <KLocalizedString>
// #include <KPIMUtils/LinkLocator>

using namespace KFbAPI;

class AttendeeInfo::AttendeeInfoPrivate : public QSharedData
{
public:
    QString name;
    QString id;
    QString status;
};

class EventInfo::EventInfoPrivate : public QSharedData
{
public:
    QJsonObject jsonData;

    QList<AttendeeInfoPtr> attendees;
};

//============================================================================================

AttendeeInfo::AttendeeInfo(const QString &name, const QString &id, const QString &status)
    : d(new AttendeeInfoPrivate)
{
    d->name = name;
    d->id = id;
    d->status = status;
}

AttendeeInfo::AttendeeInfo(const AttendeeInfo &other)
{
    d = other.d;
}

AttendeeInfo::~AttendeeInfo()
{
}

AttendeeInfo& AttendeeInfo::operator=(const AttendeeInfo &other)
{
    if (this == &other) return *this; //Protect against self-assignment
    d = other.d;
    return *this;
}


QString AttendeeInfo::name() const
{
    return d->name;
}

QString AttendeeInfo::id() const
{
    return d->id;
}

QString AttendeeInfo::status() const
{
    return d->status;
}

//============================================================================================

EventInfo::EventInfo(const QJsonObject &jsonData)
    : d(new EventInfoPrivate)
{
    d->jsonData = jsonData;
}


EventInfo::EventInfo()
    : d(new EventInfoPrivate)
{
}

EventInfo::EventInfo(const EventInfo &other)
{
    d = other.d;
}

EventInfo::~EventInfo()
{
}

EventInfo& EventInfo::operator=(const EventInfo& other)
{
    if (this == &other) return *this; //Protect against self-assignment
    d = other.d;
    return *this;
}

// EventPtr EventInfo::asEvent() const
// {
//     EventPtr event(new Event);
//     QString desc = description();
//     desc = KPIMUtils::LinkLocator::convertToHtml(desc, KPIMUtils::LinkLocator::ReplaceSmileys);
//     if (!desc.isEmpty()) {
//         desc += "<br><br>";
//     }
//     desc += "<a href=\"" + QString("http://www.facebook.com/event.php?eid=%1").arg(id()) +
//             "\">" + i18n("View Event on Facebook") + "</a>";
//
//     event->setSummary(name());
//     event->setLastModified(updatedTime());
//     event->setCreated(updatedTime()); // That's a lie, but Facebook doesn't give us the created time
//     event->setDescription(desc, true);
//     event->setLocation(location());
//     event->setHasEndDate(endTime().isValid());
//     event->setOrganizer(organizer());
//     event->setUid(id());
//     if (startTime().isValid()) {
//         event->setDtStart(startTime());
//     } else {
//         kWarning() << "WTF, event has no start date??";
//     }
//     if (endTime().isValid()) {
//         event->setDtEnd(endTime());
//     } else if (startTime().isValid() && !endTime().isValid()) {
//         // Urgh...
//         KDateTime endDate;
//         endDate.setDate(startTime().date());
//         endDate.setTime(QTime::fromString("23:59:00"));
//         kWarning() << "Event without end time: " << event->summary() << event->dtStart();
//         kWarning() << "Making it an event until the end of the day.";
//         event->setDtEnd(endDate);
//         //kWarning() << "Using a duration of 2 hours";
//         //event->setDuration(KCalCore::Duration(2 * 60 * 60, KCalCore::Duration::Seconds));
//     }
//
//     // TODO: Organizer
//     //       Public/Private -> freebusy!
//     //       venue: add to location?
//     //       picture?
//     foreach (const AttendeeInfoPtr &attendeeInfo, attendees()) {
//         AttendeePtr attendee(new Attendee(attendeeInfo->name(),
//                                     "facebook@unkown.invalid",
//                                     false,
//                                     attendeeInfo->status(),
//                                     Attendee::OptParticipant,
//                                     attendeeInfo->id()));
//         event->addAttendee(attendee);
//     }
//
//     return event;
// }

QDateTime EventInfo::endTime() const
{
    return QDateTime::fromString(d->jsonData.value(QStringLiteral("end_time")).toString(), Qt::ISODate);
}

QString EventInfo::endTimeString() const
{
    return d->jsonData.value(QStringLiteral("end_time")).toString();
}

QString EventInfo::id() const
{
    return d->jsonData.value(QStringLiteral("id")).toString();
}

QString EventInfo::location() const
{
    return d->jsonData.value(QStringLiteral("location")).toString();
}

QString EventInfo::name() const
{
    return d->jsonData.value(QStringLiteral("name")).toString();
}

QDateTime EventInfo::startTime() const
{
    return QDateTime::fromString(d->jsonData.value(QStringLiteral("start_time")).toString(), Qt::ISODate);
}

QString EventInfo::startTimeString() const
{
    return d->jsonData.value(QStringLiteral("start_time")).toString();
}

QString EventInfo::description() const
{
    return d->jsonData.value(QStringLiteral("description")).toString();
}

QString EventInfo::organizer() const
{
    return d->jsonData.value(QStringLiteral("organizer")).toString();
}

QDateTime EventInfo::updatedTime() const
{
    return QDateTime::fromString(d->jsonData.value(QStringLiteral("updated_time")).toString(), Qt::ISODate);
}

QString EventInfo::updatedTimeString() const
{
    return d->jsonData.value(QStringLiteral("updated_time")).toString();
}

QList<AttendeeInfoPtr> EventInfo::attendees() const
{
    if (d->attendees.isEmpty() && d->jsonData.value(QStringLiteral("attending_count")).toInt() > 0) {
        //TODO: a separate job for getting attendees list is needed
    }
    return d->attendees;
}
