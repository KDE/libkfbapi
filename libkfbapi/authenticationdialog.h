/* Copyright 2010 Thomas McGuire <mcguire@kde.org>

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

#ifndef KFBAPI_AUTHENTICATIONDIALOG_H
#define KFBAPI_AUTHENTICATIONDIALOG_H

#include "libkfbapi_export.h"

#include <KDialog>


namespace KFbAPI {

class AuthenticationDialogPrivate;

class LIBKFBAPI_EXPORT AuthenticationDialog : public KDialog
{
  Q_OBJECT
public:
    explicit AuthenticationDialog(QWidget *parent);
    ~AuthenticationDialog();
    void setAppId(const QString &appId);
    void setPermissions(const QStringList &permissions);
    void start();
    void setUsername(const QString &username);
    void setPassword(const QString &password);

Q_SIGNALS:
    void authenticated(const QString &accessToken);
    void canceled();

private Q_SLOTS:
    void loadFinished();
    void urlChanged(const QUrl &url);
    void showErrorDialog();

private:
    AuthenticationDialogPrivate * const d;
//     Q_DECLARE_PRIVATE(AuthenticationDialog);
};

}

#endif
