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

#include "eventinfo.h"

#include "util.h"

#include <KDebug>
#include <KLocalizedString>
#include <KPIMUtils/LinkLocator>

using namespace KFbAPI;

class EventInfo::EventInfoPrivate : public QSharedData
{
public:
    QString name;
    QString startTime;
    QString endTime;
    QString location;
    QString id;
    QString description;
    QString organizer;
    QString updatedTime;

    QList<AttendeeInfoPtr> attendees;
};

//============================================================================================

AttendeeInfo::AttendeeInfo(const QString &name, const QString &id, const Attendee::PartStat &status)
    : m_name(name),
      m_id(id),
      m_status(status)
{
}

QString AttendeeInfo::name() const
{
    return m_name;
}

QString AttendeeInfo::id() const
{
    return m_id;
}

Attendee::PartStat AttendeeInfo::status() const
{
    return m_status;
}

//============================================================================================

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

EventPtr EventInfo::asEvent() const
{
    EventPtr event(new Event);
    QString desc = description();
    desc = KPIMUtils::LinkLocator::convertToHtml(desc, KPIMUtils::LinkLocator::ReplaceSmileys);
    if (!desc.isEmpty()) {
        desc += "<br><br>";
    }
    desc += "<a href=\"" + QString("http://www.facebook.com/event.php?eid=%1").arg(id()) +
            "\">" + i18n("View Event on Facebook") + "</a>";

    event->setSummary(name());
    event->setLastModified(updatedTime());
    event->setCreated(updatedTime()); // That's a lie, but Facebook doesn't give us the created time
    event->setDescription(desc, true);
    event->setLocation(location());
    event->setHasEndDate(endTime().isValid());
    event->setOrganizer(organizer());
    event->setUid(id());
    if (startTime().isValid()) {
        event->setDtStart(startTime());
    } else {
        kWarning() << "WTF, event has no start date??";
    }
    if (endTime().isValid()) {
        event->setDtEnd(endTime());
    } else if (startTime().isValid() && !endTime().isValid()) {
        // Urgh...
        KDateTime endDate;
        endDate.setDate(startTime().date());
        endDate.setTime(QTime::fromString("23:59:00"));
        kWarning() << "Event without end time: " << event->summary() << event->dtStart();
        kWarning() << "Making it an event until the end of the day.";
        event->setDtEnd(endDate);
        //kWarning() << "Using a duration of 2 hours";
        //event->setDuration(KCalCore::Duration(2 * 60 * 60, KCalCore::Duration::Seconds));
    }

    // TODO: Organizer
    //       Public/Private -> freebusy!
    //       venue: add to location?
    //       picture?
    foreach (const AttendeeInfoPtr &attendeeInfo, attendees()) {
        AttendeePtr attendee(new Attendee(attendeeInfo->name(),
                                    "facebook@unkown.invalid",
                                    false,
                                    attendeeInfo->status(),
                                    Attendee::OptParticipant,
                                    attendeeInfo->id()));
        event->addAttendee(attendee);
    }

    return event;
}

KDateTime EventInfo::endTime() const
{
    return facebookTimeToKDateTime(d->endTime);
}

QString EventInfo::endTimeString() const
{
    return d->endTime;
}

QString EventInfo::id() const
{
    return d->id;
}

QString EventInfo::location() const
{
    return d->location;
}

QString EventInfo::name() const
{
    return d->name;
}

void EventInfo::setEndTimeString(const QString &endTime)
{
    d->endTime = endTime;
}

void EventInfo::setId(const QString &id)
{
    d->id = id;
}

void EventInfo::setLocation(const QString &location)
{
    d->location = location;
}

void EventInfo::setName(const QString &name)
{
    d->name = name;
}

void EventInfo::setStartTimeString(const QString &startTime)
{
    d->startTime = startTime;
}

KDateTime EventInfo::startTime() const
{
    return facebookTimeToKDateTime(d->startTime);
}

QString EventInfo::startTimeString() const
{
    return d->startTime;
}

QString EventInfo::description() const
{
    return d->description;
}

void EventInfo::setDescription(const QString &description)
{
    d->description = description;
}

QString EventInfo::organizer() const
{
    return d->organizer;
}

void EventInfo::setOrganizer(const QString &organizer)
{
    d->organizer = organizer;
}

void EventInfo::setUpdatedTimeString(const QString &updatedTime)
{
    d->updatedTime = updatedTime;
}

KDateTime EventInfo::updatedTime() const
{
    return facebookTimeToKDateTime(d->updatedTime);
}

QString EventInfo::updatedTimeString() const
{
    return d->updatedTime;
}

void EventInfo::addAttendees(const QList<AttendeeInfoPtr> &attendees)
{
    d->attendees << attendees;
}

QList<AttendeeInfoPtr> EventInfo::attendees() const
{
    return d->attendees;
}
