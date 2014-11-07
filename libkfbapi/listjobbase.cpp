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

#include "listjobbase.h"
#include "listjobbase_p.h"

#include <QVariant>
#include <QJsonObject>
#include <QJsonArray>
#include <QDebug>

using namespace KFbAPI;

ListJobBase::ListJobBase(const QString &path, const QString &accessToken, bool multiResult, QObject *parent)
    : FacebookGetJob(*new ListJobBasePrivate, path, accessToken, parent)
{
    Q_D(ListJobBase);
    d->multiResult = multiResult;
}

ListJobBase::~ListJobBase()
{
}

void ListJobBase::handleData(const QJsonDocument &data)
{
    Q_D(ListJobBase);
    if (!d->multiResult) {
        handleItems(data);
    } else {
        const QJsonArray dataArray = data.object().value(QStringLiteral("data")).toArray();


        for (int i = 0; i < dataArray.size(); i++) {
            handleItem(dataArray.at(i).toObject());
        }
    }

    QJsonObject pagingObject = data.object().value(QStringLiteral("paging")).toObject();

    qDebug() << pagingObject;

    d->nextPage = pagingObject.value(QStringLiteral("next")).toString();
    d->prevPage = pagingObject.value(QStringLiteral("previous")).toString();
}

void ListJobBase::handleItems(const QJsonDocument &data)
{
}

QString ListJobBase::nextItems() const
{
    Q_D(const ListJobBase);
    return d->nextPage;
}

QString ListJobBase::previousItems() const
{
    Q_D(const ListJobBase);
    return d->prevPage;
}
