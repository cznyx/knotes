/*
   Copyright (C) 2013-2018 Montel Laurent <montel@kde.org>

   This program is free software; you can redistribute it and/or
   modify it under the terms of the GNU General Public
   License as published by the Free Software Foundation; either
   version 2 of the License, or (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; see the file COPYING.  If not, write to
   the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.
*/
#ifndef NOTESMANAGER_H
#define NOTESMANAGER_H

#include <QObject>

#include "notesagentalarmdialog.h"

#include <Item>
#include <QPointer>
class QTcpServer;
class QTimer;
namespace NoteShared {
class NotesChangeRecorder;
class NotesAkonadiTreeModel;
}

namespace Akonadi {
class Session;
}

class QModelIndex;
class NotesManager : public QObject
{
    Q_OBJECT
public:
    explicit NotesManager(QObject *parent = nullptr);
    ~NotesManager();

    void stopAll();
    void updateNetworkListener();

public Q_SLOTS:
    void load();

private Q_SLOTS:
    void slotAcceptConnection();
    void slotNewNote(const QString &name, const QString &text);
    void slotCheckAlarm();

    void slotItemAdded(const Akonadi::Item &item);
    void slotItemRemoved(const Akonadi::Item &item);
    void slotItemChanged(const Akonadi::Item &item, const QSet<QByteArray> &set);

    void slotCollectionsReceived(const Akonadi::Collection::List &collections);
private:
    void clear();
    Akonadi::Item::List mListItem;
    QTcpServer *mListener = nullptr;
    QTimer *mCheckAlarm = nullptr;
    NoteShared::NotesChangeRecorder *mNoteRecorder = nullptr;
    Akonadi::Session *mSession = nullptr;
    QPointer<NotesAgentAlarmDialog> mAlarmDialog;
};

#endif // NOTESMANAGER_H
