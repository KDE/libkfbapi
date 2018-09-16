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

#ifndef KFBAPI_COMMENTINFOPARSER_P_H
#define KFBAPI_COMMENTINFOPARSER_P_H

#include "commentinfo.h"

#include <QObject>

namespace KFbAPI {

class CommentDataParser : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString id WRITE setId READ id)
    Q_PROPERTY(QVariantMap from WRITE setFrom READ fromMap)
    Q_PROPERTY(QString message WRITE setMessage READ message)
    Q_PROPERTY(QString created_time WRITE setCreatedTimeString READ createdTimeString)
    Q_PROPERTY(int likes WRITE setLikes READ likes)

public:
    void setDataObject(const CommentData &commentData) {m_commentData = commentData;}
    CommentData dataObject() const {return m_commentData;}

    void setId(const QString &id) {m_commentData.setId(id);}
    QString id() const {return m_commentData.id();}

    void setFrom(const QVariantMap &from) {m_commentData.setFrom(from);}
    QVariantMap fromMap() const {return m_commentData.fromMap();}

    void setMessage(const QString &message) {m_commentData.setMessage(message);}
    QString message() const {return m_commentData.message();}

    void setCreatedTimeString(const QString &createdTimeString) {m_commentData.setCreatedTimeString(createdTimeString);}
    QString createdTimeString() const {return m_commentData.createdTimeString();}

    void setLikes(int likes) {m_commentData.setLikes(likes);}
    int likes() const {return m_commentData.likes();}

private:
    CommentData m_commentData;
};

//=========================================================================================

class CommentInfoParser : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QVariantList data WRITE setDataList READ dataList)
    Q_PROPERTY(int count WRITE setCount READ count)

public:
    void setDataObject(const CommentInfo &commentInfo) {m_commentInfo = commentInfo;}
    CommentInfo dataObject() const {return m_commentInfo;}

    void setDataList(const QVariantList &data) {m_commentInfo.setData(data);}
    QVariantList dataList() const {return m_commentInfo.dataList();}

    void setCount(int count) {m_commentInfo.setCount(count);}
    int count() const {return m_commentInfo.count();}

private:
    CommentInfo m_commentInfo;

};

}

#endif
