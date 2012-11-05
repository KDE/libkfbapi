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

#ifndef KFBAPI_APPINFOPARSER_H
#define KFBAPI_APPINFOPARSER_H

#include "appinfo.h"

#include <QObject>
#include <QUrl>

namespace KFbAPI {

class AppInfoParser : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString id WRITE setId READ id)
    Q_PROPERTY(QString name WRITE setName READ name)
    Q_PROPERTY(QString description WRITE setDescription READ description)
    Q_PROPERTY(QString category WRITE setCategory READ category)
    Q_PROPERTY(QString company WRITE setCompany READ company)
    Q_PROPERTY(QUrl icon_url WRITE setIconUrl READ iconUrl)
    Q_PROPERTY(QString subcategory WRITE setSubcategory READ subcategory)
    Q_PROPERTY(QUrl link WRITE setLink READ link)
    Q_PROPERTY(QUrl logo_url WRITE setLogoUrl READ logoUrl)

public:
    void setDataObject(const AppInfo &appInfo) {m_appInfo = appInfo;}
    AppInfo dataObject() const {return m_appInfo;}

    void setId(const QString &id) {m_appInfo.setId(id);}
    QString id() const {return m_appInfo.id();}

    void setName(const QString &name) {m_appInfo.setName(name);}
    QString name() const {return m_appInfo.name();}

    void setDescription(const QString &description) {m_appInfo.setDescription(description);}
    QString description() const {return m_appInfo.description();}

    void setCategory(const QString &category) {m_appInfo.setCategory(category);}
    QString category() const {return m_appInfo.category();}

    void setCompany(const QString &company) {m_appInfo.setCompany(company);}
    QString company() const {return m_appInfo.company();}

    void setIconUrl(const QUrl &iconUrl) {m_appInfo.setIconUrl(iconUrl);}
    QUrl iconUrl() const {return m_appInfo.iconUrl();}

    void setSubcategory(const QString &subcategory) {m_appInfo.setSubcategory(subcategory);}
    QString subcategory() const {return m_appInfo.subcategory();}

    void setLink(const QUrl &link) {m_appInfo.setLink(link);}
    QUrl link() const {return m_appInfo.link();}

    void setLogoUrl(const QUrl &logoUrl) {m_appInfo.setLogoUrl(logoUrl);}
    QUrl logoUrl() const {return m_appInfo.logoUrl();}

private:
    AppInfo m_appInfo;
};

}

#endif
