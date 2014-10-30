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

#include "eventjob.h"
#include "facebookjobs_p.h"

using namespace KFbAPI;

class KFbAPI::EventJobPrivate : public KFbAPI::FacebookGetJobPrivate {
public:
    QStringList eventFields() const;
//     QList<AttendeeInfoPtr> attendees(const QVariantMap &dataMap, const QString &facebookKey,
//                                      Attendee::PartStat status);

    QList<EventInfo> eventInfo;
};

QStringList EventJobPrivate::eventFields() const
{
    QStringList fields;
    fields << QStringLiteral("owner")
            << QStringLiteral("name")
            << QStringLiteral("description")
            << QStringLiteral("start_time")
            << QStringLiteral("end_time")
            << QStringLiteral("location")
            << QStringLiteral("venue")
            << QStringLiteral("privacy")
            << QStringLiteral("updated_time")
            << QStringLiteral("noreply")
            << QStringLiteral("maybe")
            << QStringLiteral("attending")
            << QStringLiteral("declined");

    return fields;
}
/*
QList<AttendeeInfoPtr> EventJobPrivate::attendees(const QVariantMap &dataMap, const QString &facebookKey,
                                                  Attendee::PartStat status)
{
    QList<AttendeeInfoPtr> retVal;
    const QVariantList list = dataMap.value(facebookKey).toMap().value("data").toList();

    Q_FOREACH (const QVariant &attendee, list) {
        const QVariantMap map = attendee.toMap();
        AttendeeInfoPtr attendeeInfo(new AttendeeInfo(map["name"].toString(),
                                                      map["id"].toString(), status));
        retVal << attendeeInfo;
    }

    return retVal;
}*/

//-----------------------------------------------------------------------------

EventJob::EventJob(const QString &eventId, const QString &accessToken, QObject *parent)
    : FacebookGetIdJob(*new EventJobPrivate, eventId, accessToken, parent)
{
    Q_D(EventJob);
    setFields(d->eventFields());
}

EventJob::EventJob(const QStringList &eventIds, const QString &accessToken, QObject *parent)
  : FacebookGetIdJob(*new EventJobPrivate, eventIds, accessToken, parent)
{
    Q_D(EventJob);
    setFields(d->eventFields());
}

QList<EventInfo> EventJob::eventInfo() const
{
    Q_D(const EventJob);
    return d->eventInfo;
}

void EventJob::handleSingleData(const QJsonDocument &data)
{
    Q_D(EventJob);

    EventInfo eventInfo(data.object());

//     eventInfo.addAttendees(d->attendees(dataMap, "noreply", Attendee::NeedsAction));
//     eventInfo.addAttendees(d->attendees(dataMap, "maybe", Attendee::Tentative));
//     eventInfo.addAttendees(d->attendees(dataMap, "attending", Attendee::Accepted));
//     eventInfo.addAttendees(d->attendees(dataMap, "declined", Attendee::Declined));

    d->eventInfo.append(eventInfo);
}

#include "eventjob.moc"
