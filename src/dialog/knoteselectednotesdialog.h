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
#ifndef KNOTESELECTEDNOTESDIALOG_H
#define KNOTESELECTEDNOTESDIALOG_H

#include <QDialog>
#include <AkonadiCore/Item>
class QListWidget;
class KNote;
class QPushButton;
class KNoteSelectedNotesDialog : public QDialog
{
    Q_OBJECT
public:
    explicit KNoteSelectedNotesDialog(QWidget *parent = nullptr);
    ~KNoteSelectedNotesDialog();

    void setNotes(const QHash<Akonadi::Item::Id, KNote *> &notes);

    QStringList selectedNotes() const;

private Q_SLOTS:
    void slotSelectionChanged();

private:
    enum listViewData {
        AkonadiId = Qt::UserRole + 1
    };

    void writeConfig();
    void readConfig();
    QListWidget *mListNotes = nullptr;
    QHash<Akonadi::Item::Id, KNote *> mNotes;
    QPushButton *mOkButton = nullptr;
};

#endif // KNOTESELECTEDNOTESDIALOG_H
