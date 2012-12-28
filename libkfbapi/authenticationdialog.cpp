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

#include "authenticationdialog.h"

#include <KLocale>
#include <KWebView>
#include <KMessageBox>
#include <KDebug>

#include <QVBoxLayout>
#include <QTimer>
#include <QLabel>
#include <QProgressBar>
#include <QWebFrame>
#include <QWebElement>

using namespace KFbAPI;

class KFbAPI::AuthenticationDialogPrivate {
public:
    QString appId;
    QStringList permissions;
    KWebView *webView;
    QProgressBar *progressBar;
    QString error;
    QString errorReason;
    QString errorDescription;
    QString username;
    QString password;
};

//-----------------------------------------------------------------------------

AuthenticationDialog::AuthenticationDialog(QWidget *parent)
    : KDialog(parent),
      d(new AuthenticationDialogPrivate)
{
//     Q_D(AuthenticationDialog);
    setButtons(KDialog::Cancel);
    setCaption(i18n("Authenticate with Facebook"));
    setAttribute(Qt::WA_DeleteOnClose, true);

    QWidget * const widget = new QWidget(this);
    QVBoxLayout * const layout = new QVBoxLayout(widget);
    QWidget * const progressWidget = new QWidget(this);
    QHBoxLayout * const progressLayout = new QHBoxLayout(progressWidget);
    progressLayout->setMargin(0);
    layout->setMargin(0);
    setMainWidget(widget);
    d->webView = new KWebView(this);

    d->progressBar = new QProgressBar(this);
    d->progressBar->setRange(0, 100);
    QLabel * const progressLabel = new QLabel(i18n("Loading Page:"), this);
    progressLayout->addWidget(progressLabel);
    progressLayout->addWidget(d->progressBar);

    layout->addWidget(progressWidget);
    layout->addWidget(d->webView);

    connect(this, SIGNAL(cancelClicked()), SIGNAL(canceled()));
    connect(d->webView, SIGNAL(urlChanged(QUrl)), this, SLOT(urlChanged(QUrl)));
    connect(d->webView, SIGNAL(loadStarted()), progressWidget, SLOT(show()));
    connect(d->webView, SIGNAL(loadFinished(bool)), progressWidget, SLOT(hide()));
    connect(d->webView, SIGNAL(loadFinished(bool)), this, SLOT(loadFinished()));
    connect(d->webView, SIGNAL(loadProgress(int)), d->progressBar, SLOT(setValue(int)));
}

void AuthenticationDialog::setAppId(const QString &appId)
{
//     Q_D(AuthenticationDialog);
    d->appId = appId;
}

void AuthenticationDialog::setPermissions(const QStringList &permissions)
{
//     Q_D(AuthenticationDialog);
    d->permissions = permissions;
}

void AuthenticationDialog::start()
{
//     Q_D(AuthenticationDialog);
    Q_ASSERT(!d->appId.isEmpty());

    const QString url = QString("https://graph.facebook.com/oauth/authorize?"
                               "client_id=%1&"
                               "redirect_uri=http://www.facebook.com/connect/login_success.html&"
                               "type=user_agent&"
                               "scope=%2").arg(d->appId)
                                          .arg(d->permissions.join(","));

    kDebug() << "Showing" << url;
    d->webView->setUrl(QUrl::fromUserInput(url));
    show();
}

void AuthenticationDialog::setUsername(const QString &username)
{
//     Q_D(AuthenticationDialog);
    d->username = username;
}

void AuthenticationDialog::setPassword(const QString &password)
{
//     Q_D(AuthenticationDialog);
    d->password = password;
}

void AuthenticationDialog::showErrorDialog()
{
//   hide();
//   const QString details = i18n("<b>Facebook Error Description:</b> %1<br>"
//                                 "<b>Facebook Error:</b> %2<br>"
//                                 "<b>Facebook Error Reason:</b> %3", d->errorDescription, d->error, d->errorReason);
//   KMessageBox::detailedSorry(this, i18n("Authentication with Facebook was not successful."),
//                               details, i18n("Authentication Problem."));
//   emit canceled();
//   close();
}

void AuthenticationDialog::loadFinished()
{
//     Q_D(AuthenticationDialog);
    QUrl url = d->webView->url();

    if (url.host() == "www.facebook.com" && url.path() == "/login.php") {
        if (d->username.isEmpty() && d->password.isEmpty()) {
            return;
        }

        QWebFrame *frame = d->webView->page()->mainFrame();
        if (!d->username.isEmpty()) {
            QWebElement email = frame->findFirstElement("input#email");
            if (!email.isNull()) {
                email.setAttribute("value", d->username);
            }
        }

        if (!d->password.isEmpty()) {
            QWebElement passd = frame->findFirstElement("input#pass");
            if (!passd.isNull()) {
                passd.setAttribute("value", d->password);
            }
        }
        return;
    }
}

void AuthenticationDialog::urlChanged(const QUrl &url)
{
//     Q_D(AuthenticationDialog);
    kDebug() << "Navigating to" << url;

    if (url.host() == "www.facebook.com" && url.path() == "/connect/login_success.html") {
        d->errorReason = url.queryItemValue("error_reason");
        d->error = url.queryItemValue("error");
        d->errorDescription = url.queryItemValue("error_description").replace('+', ' ');
        if (!d->error.isEmpty() || !d->errorReason.isEmpty() || !d->errorDescription.isEmpty()) {
            QTimer::singleShot(0, this, SLOT(showErrorDialog()));
            return;
        }

        // The URL comes in the form "bla#access_token=bla&expires_in=foo", we need to convert from
        // # to ?
        const QUrl fixedURL = QUrl::fromUserInput(url.toString().replace('#', '?'));
        const QString accessToken = fixedURL.queryItemValue("access_token");
        if (!accessToken.isEmpty()) {
            emit authenticated(accessToken);
            accept();
        }
    }
}

#include "authenticationdialog.moc"
