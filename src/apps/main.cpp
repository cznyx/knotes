/*******************************************************************
 KNotes -- Notes for the KDE project

 Copyright (c) 1997-2015, The KNotes Developers

 This program is free software; you can redistribute it and/or
 modify it under the terms of the GNU General Public License
 as published by the Free Software Foundation; either version 2
 of the License, or (at your option) any later version.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with this program; if not, write to the Free Software
 Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
*******************************************************************/

#include <config-knotes.h>
#include "knotes_debug.h"
#include "knotes_options.h"
#include "knotes-version.h"
#include "apps/application.h"
#include <KLocalizedString>
#include <kdelibs4configmigrator.h>
#include "notes/knotesmigrateapplication.h"

#include <KAboutData>
#include <KCrash>
#include <KLocalizedString>

#include <QApplication>
#include <QCommandLineParser>
#include <KCrash>

void knotesOptions(QCommandLineParser *parser);
void knotesAuthors(KAboutData &aboutData);

int main(int argc, char *argv[])
{
    // Disable session management
    qunsetenv("SESSION_MANAGER");

    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    Application app(argc, &argv);
    app.setAttribute(Qt::AA_UseHighDpiPixmaps, true);
    KCrash::initialize();
    KNotesMigrateApplication migrate;
    migrate.migrate();

    KAboutData aboutData(QStringLiteral("knotes"),
                         i18n("KNotes"),
                         QStringLiteral(KNOTES_VERSION),
                         i18n("KDE Notes"),
                         KAboutLicense::GPL,
                         i18n("Copyright © 1997–2018 KNotes authors"));
    knotesAuthors(aboutData);
    app.setAboutData(aboutData);
    QCommandLineParser *cmdArgs = app.cmdArgs();
    knotesOptions(cmdArgs);

    const QStringList args = QApplication::arguments();
    cmdArgs->process(args);
    aboutData.processCommandLine(cmdArgs);

    if (!Application::start(args)) {
        qCDebug(KNOTES_LOG) << " knotes already started";
        return 0;
    }

    return app.exec();
}

void knotesAuthors(KAboutData &aboutData)
{
    aboutData.addAuthor(i18n("Laurent Montel"),
                        i18n("Maintainer"),
                        QStringLiteral("montel@kde.org"));
    aboutData.addAuthor(i18n("Guillermo Antonio Amaral Bastidas"),
                        i18n("Previous Maintainer"),
                        QStringLiteral("me@guillermoamaral.com"));
    aboutData.addAuthor(i18n("Michael Brade"),
                        i18n("Previous Maintainer"),
                        QStringLiteral("brade@kde.org"));
    aboutData.addAuthor(i18n("Bernd Johannes Wuebben"),
                        i18n("Original KNotes Author"),
                        QStringLiteral("wuebben@kde.org"));
    aboutData.addAuthor(i18n("Wynn Wilkes"),
                        i18n("Ported KNotes to KDE 2"),
                        QStringLiteral("wynnw@calderasystems.com"));
    aboutData.addAuthor(i18n("Daniel Martin"),
                        i18n("Network Interface"),
                        QStringLiteral("daniel.martin@pirack.com"));
    aboutData.addAuthor(i18n("Bo Thorsen"),
                        i18n("Started KDE Resource Framework Integration"),
                        QStringLiteral("bo@sonofthor.dk"));
    aboutData.addCredit(i18n("Bera Debajyoti"),
                        i18n("Idea and initial code for the new look & feel"),
                        QStringLiteral("debajyotibera@gmail.com"));
    aboutData.addCredit(i18n("Matthias Ettrich"),
                        QString(),
                        QStringLiteral("ettrich@kde.org"));
    aboutData.addCredit(i18n("David Faure"),
                        QString(),
                        QStringLiteral("faure@kde.org"));
    aboutData.addCredit(i18n("Matthias Kiefer"),
                        QString(),
                        QStringLiteral("kiefer@kde.org"));
    aboutData.addCredit(i18n("Luboš Luňák"),
                        QStringLiteral("l.lunak@kde.org"));
    aboutData.addCredit(i18n("Dirk A. Mueller"),
                        QString(),
                        QStringLiteral("dmuell@gmx.net"));
    aboutData.addCredit(i18n("Carsten Pfeiffer"),
                        QString(),
                        QStringLiteral("pfeiffer@kde.org"));
    aboutData.addCredit(i18n("Harri Porten"),
                        QString(),
                        QStringLiteral("porten@kde.org"));
    aboutData.addCredit(i18n("Espen Sand"),
                        QString(),
                        QStringLiteral("espen@kde.org"));
}
