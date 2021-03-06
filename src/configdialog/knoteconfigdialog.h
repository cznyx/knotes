/*******************************************************************
 KNotes -- Notes for the KDE project

 Copyright (c) 1997-2005, The KNotes Developers

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

#ifndef KNOTECONFIGDIALOG_H
#define KNOTECONFIGDIALOG_H

#include "knotes_export.h"

#include <KCModule>
#include <KCMultiDialog>

class KNoteCollectionConfigWidget;
class KNotePrintSelectThemeComboBox;

class QLineEdit;

class KNOTES_EXPORT KNoteConfigDialog : public KCMultiDialog
{
    Q_OBJECT
public:
    explicit KNoteConfigDialog(const QString &title, QWidget *parent);
    ~KNoteConfigDialog();

public Q_SLOTS:
    void slotOk();
};

class KNoteDisplayConfig : public KCModule
{
    Q_OBJECT
public:
    explicit KNoteDisplayConfig(QWidget *parent);
    /** Reimplemented from KCModule. */
    void load() override;
    void save() override;
};

class KNoteEditorConfig : public KCModule
{
    Q_OBJECT
public:
    explicit KNoteEditorConfig(QWidget *parent);
    /** Reimplemented from KCModule. */
    void load() override;
    void save() override;
};

class KNoteMiscConfig : public KCModule
{
    Q_OBJECT
public:
    explicit KNoteMiscConfig(QWidget *parent);
    /** Reimplemented from KCModule. */
    void load() override;
    void save() override;
    void defaults() override;
private Q_SLOTS:
    void slotHelpLinkClicked(const QString &);
private:
    QLineEdit *mDefaultTitle = nullptr;
};

class KNotePrintConfig : public KCModule
{
    Q_OBJECT
public:
    explicit KNotePrintConfig(QWidget *parent);
    /** Reimplemented from KCModule. */
    void load() override;
    void save() override;
    void defaults() override;

private Q_SLOTS:
    void slotThemeChanged();
    void slotDownloadNewThemes();

private:
    KNotePrintSelectThemeComboBox *mSelectTheme = nullptr;
};

class KNoteCollectionConfig : public KCModule
{
    Q_OBJECT
public:
    explicit KNoteCollectionConfig(QWidget *parent);
    /** Reimplemented from KCModule. */
    void load() override;
    void save() override;

private:
    KNoteCollectionConfigWidget *mCollectionConfigWidget = nullptr;
};

#endif
