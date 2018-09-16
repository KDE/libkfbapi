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

#ifndef KFBAPI_PROPERTYINFOPARSER_P_H
#define KFBAPI_PROPERTYINFOPARSER_P_H

#include "propertyinfo.h"

#include <QObject>

namespace KFbAPI {

class PropertyInfoParser : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString name WRITE setName READ name)
    Q_PROPERTY(QString text WRITE setText READ text)
    Q_PROPERTY(QString href WRITE setHref READ href)

public:
    void setDataObject(const PropertyInfo &propertyInfo) {m_propertyInfo = propertyInfo;}
    PropertyInfo dataObject() const {return m_propertyInfo;}

    void setName(const QString &name) {m_propertyInfo.setName(name);}
    QString name() const {return m_propertyInfo.name();}

    void setText(const QString &text) {m_propertyInfo.setText(text);}
    QString text() const {return m_propertyInfo.text();}

    void setHref(const QString &href) {m_propertyInfo.setHref(href);}
    QString href() const {return m_propertyInfo.href();}

private:
    PropertyInfo m_propertyInfo;
};

}

#endif
