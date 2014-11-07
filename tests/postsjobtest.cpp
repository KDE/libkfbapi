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

#include "../libkfbapi/likeinfo.h"
#include "../libkfbapi/likesjob.h"
#include "../libkfbapi/postinfo.h"
#include "../libkfbapi/postjob.h"
#include "../libkfbapi/postcompositejob.h"

void startJob(const QString &accessToken) {
    KFbAPI::PostCompositeJob *postsCompositeJob = new KFbAPI::PostCompositeJob(QString(), KFbAPI::PostInfo::FetchCountsOnly, accessToken);
    QObject::connect(postsCompositeJob, &KFbAPI::PostCompositeJob::finished, [=](KJob *job) {
        QList<KFbAPI::PostInfo> postsList = qobject_cast<KFbAPI::PostCompositeJob*>(job)->posts();
        Q_FOREACH (const KFbAPI::PostInfo &post, postsList) {
            qDebug() << "===============================================================================";
            qDebug() << post.from().name() << post.message();
            qDebug() << "Likes:" << post.likes().count() << "| Comments:" << post.comments().count();
            qDebug();
        }
    });

    postsCompositeJob->start();
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
    cmd.addOption(accessTokenOption);
    cmd.process(app);

    if (cmd.isSet(accessTokenOption)) {
        // QCommandLineOption ensures it's not passed empty
        startJob(cmd.value(accessTokenOption));
        return app.exec();
    } else {
#ifdef HAVE_KACCOUNTS
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
        startJob(qobject_cast<GetCredentialsJob*>(job)->credentialsData()[QStringLiteral("AccessToken")].toString());
    });

    job->start();
    return app.exec();
#else
    qDebug() << "No access token passed and KAccounts not available, quitting...";
#endif
    }
}
