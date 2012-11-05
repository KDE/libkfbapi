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

#ifndef KFBAPI_POSTINFOPARSER_H
#define KFBAPI_POSTINFOPARSER_H

#include "postinfo.h"

#include <QObject>
#include <QVariantMap>

namespace KFbAPI {

class PostInfoParser : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString id WRITE setId READ id)
    Q_PROPERTY(QVariantMap from WRITE setFrom)
    Q_PROPERTY(QString message WRITE setMessage READ message)
    Q_PROPERTY(QString picture WRITE setPictureUrl READ pictureUrl)
    Q_PROPERTY(QString link WRITE setLink READ link)
    Q_PROPERTY(QString name WRITE setName READ name)
    Q_PROPERTY(QString caption WRITE setCaption READ caption)
    Q_PROPERTY(QString description WRITE setDescription READ description)
    Q_PROPERTY(QString source WRITE setSource READ source)
    Q_PROPERTY(QVariantList properties WRITE setProperties)
    Q_PROPERTY(QString icon WRITE setIcon READ icon)
    Q_PROPERTY(QString type WRITE setType READ type)
    Q_PROPERTY(QVariantMap likes WRITE setLikes READ likesMap)
    Q_PROPERTY(QString story WRITE setStory READ story)
    Q_PROPERTY(QVariantMap comments WRITE setComments READ commentsMap)
    Q_PROPERTY(QVariantMap application WRITE setApplication)
    Q_PROPERTY(QString created_time WRITE setCreatedTimeString READ createdTimeString)
    Q_PROPERTY(QString updated_time WRITE setUpdatedTimeString READ updatedTimeString)

public:
    void setDataObject(const PostInfo &postInfo) {m_postInfo = postInfo;}
    PostInfo dataObject() const {return m_postInfo;}

    void setId(const QString &id) {m_postInfo.setId(id);}
    QString id() const {return m_postInfo.id();}

    void setFrom(const QVariantMap &from) {m_postInfo.setFrom(from);}
//     QString () const {return m_postInfo;}

    void setMessage(const QString &message) {m_postInfo.setMessage(message);}
    QString message() const {return m_postInfo.message();}

    void setPictureUrl(const QString &pictureUrl) {m_postInfo.setPictureUrl(pictureUrl);}
    QString pictureUrl() const {return m_postInfo.pictureUrl();}

    void setLink(const QString &link) {m_postInfo.setLink(link);}
    QString link() const {return m_postInfo.link();}

    void setName(const QString &name) {m_postInfo.setName(name);}
    QString name() const {return m_postInfo.name();}

    void setCaption(const QString &caption) {m_postInfo.setCaption(caption);}
    QString caption() const {return m_postInfo.caption();}

    void setDescription(const QString &description) {m_postInfo.setDescription(description);}
    QString description() const {return m_postInfo.description();}

    void setSource(const QString &source) {m_postInfo.setSource(source);}
    QString source() const {return m_postInfo.source();}

    void setProperties(const QVariantList &properties) {m_postInfo.setProperties(properties);}
//     QString () const {return m_postInfo;}

    void setIcon(const QString &icon) {m_postInfo.setIcon(icon);}
    QString icon() const {return m_postInfo.icon();}

    void setType(const QString &type) {m_postInfo.setType(type);}
    QString type() const {return m_postInfo.type();}

    void setLikes(const QVariantMap &likes) {m_postInfo.setLikes(likes);}
    QVariantMap likesMap() const {return m_postInfo.likesMap();}

    void setStory(const QString &story) {m_postInfo.setStory(story);}
    QString story() const {return m_postInfo.story();}

    void setComments(const QVariantMap &comments) {m_postInfo.setComments(comments);}
    QVariantMap commentsMap() const {return m_postInfo.commentsMap();}

    void setApplication(const QVariantMap &application) {m_postInfo.setApplication(application);}
//     QVariantMap () const {return m_postInfo.application();}

    void setCreatedTimeString(const QString &createdTimeString) {m_postInfo.setCreatedTimeString(createdTimeString);}
    QString createdTimeString() const {return m_postInfo.createdTimeString();}

    void setUpdatedTimeString(const QString &updatedTimeString) {m_postInfo.setUpdatedTimeString(updatedTimeString);}
    QString updatedTimeString() const {return m_postInfo.updatedTimeString();}

private:
    PostInfo m_postInfo;
};

}

#endif
