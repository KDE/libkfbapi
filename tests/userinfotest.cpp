/*
    Copyright 2014 Martin Klapetek <mklapetek@kde.org>

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Library General Public
    License as published by the Free Software Foundation; either
    version 2 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Library General Public License for more details.

    You should have received a copy of the GNU Library General Public License
    along with this library; see the file COPYING.LIB.  If not, write to
    the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
    Boston, MA 02110-1301, USA.
*/

#include <QCoreApplication>
#include <QDebug>
#include <QObject>
#include <QCommandLineParser>

#include <KJob>

#ifdef HAVE_KACCOUNTS
#include <KAccounts/getcredentialsjob.h>
#include <KAccounts/core.h>
#include <Accounts/manager.h>
#endif

#include "../libkfbapi/userinfojob.h"
#include "../libkfbapi/userinfo.h"

void startJob(const QString &accessToken, const QString &userId)
{
    if (userId == QLatin1String("me")) {
        qDebug() << "No user ID specified, querying the logged in user...";
    }
    KFbAPI::UserInfoJob *userInfojob = new KFbAPI::UserInfoJob(userId, accessToken);
    QObject::connect(userInfojob, &KFbAPI::UserInfoJob::finished, [=](KJob *userJob) {
        const KFbAPI::UserInfo user = qobject_cast<KFbAPI::UserInfoJob*>(userJob)->userInfo();
        qDebug() << "  User id:" << user.id();
        qDebug() << "User name:" << user.name();
    });

    userInfojob->start();
}

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);
    QCommandLineParser cmd;
    cmd.addHelpOption();

    QCommandLineOption accessTokenOption(QStringList() << "accessToken" << "a", "A valid access token that will be used for querying Facebook servers. \
                                                                                 If this is not used and the test was built with KAccounts support, \
                                                                                 it will use KAccounts for obtaining the access token (obviously requires \
                                                                                 Facebook account to be configured in KAccounts)", "token");

    QCommandLineOption userIdOption(QStringList() << "userId" << "u", "A Facebook username ID to retrieve, if none set, it will query for the user \
                                                                       that has signed in for the given access token", "id", "me");
    cmd.addOption(userIdOption);
    cmd.addOption(accessTokenOption);
    cmd.process(app);

    if (cmd.isSet(accessTokenOption)) {
        // QCommandLineOption ensures it's not passed empty
        startJob(cmd.value(accessTokenOption), cmd.value(userIdOption));
        return app.exec();
    } else {
#ifdef HAVE_KACCOUNTS
        const QString userId = cmd.value(userIdOption);
        auto accountsList = KAccounts::accountsManager()->accountList();

        Accounts::Account *facebookAccount;

        Q_FOREACH(Accounts::AccountId a, accountsList) {
            Accounts::Account *account = KAccounts::accountsManager()->account(a);
            qDebug() << account->providerName();
            if (account->providerName() == QLatin1String("facebook")) {
                facebookAccount = account;
                break;
            }
        }

        GetCredentialsJob *job = new GetCredentialsJob(facebookAccount->id(), 0);
        QObject::connect(job, &GetCredentialsJob::finished, [=](KJob *job) {
            startJob(qobject_cast<GetCredentialsJob*>(job)->credentialsData()[QStringLiteral("AccessToken")].toString(), userId);
        });

        job->start();
        return app.exec();
#else
        qDebug() << "No access token passed and KAccounts not available, quitting...";
#endif
    }
}
