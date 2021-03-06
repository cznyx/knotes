/*******************************************************************
 KNotes -- Notes for the KDE project

 Copyright (c) 1997-2013, The KNotes Developers

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

#ifndef KNOTE_H
#define KNOTE_H

#include <config-knotes.h>
#include "knoteinterface.h"

#include <AkonadiCore/Item>

#include <KSharedConfig>
#include <KXMLGUIClient>

#include <QDomDocument>
#include <QEvent>
#include <QFrame>

class KNoteButton;
class KNoteDisplaySettings;
class KNoteEdit;

class KSelectAction;
class KToggleAction;
class KToolBar;

class QLabel;
class QMenu;
class QSizeGrip;

class KNote : public QFrame, virtual public KXMLGUIClient, public KNoteInterface
{
    Q_OBJECT
public:
    explicit KNote(const QDomDocument &buildDoc, const Akonadi::Item &item, bool allowAkonadiSearchDebug = false, QWidget *parent = nullptr);
    ~KNote();

    void setChangeItem(const Akonadi::Item &item, const QSet<QByteArray> &set = QSet<QByteArray>());
    void saveNote(bool force = false, bool sync = false);

    QString name() const;
    QString text() const;
    Akonadi::Item::Id noteId() const;

    Akonadi::Item item() const;

    void setName(const QString &name);
    void setText(const QString &text);

    bool isModified() const;
    bool isDesktopAssigned() const;

    void toDesktop(int desktop);

public Q_SLOTS:
    void slotRename();
    void slotKill(bool force = false);
    void slotClose();

Q_SIGNALS:
    void sigRequestNewNote();
    void sigShowNextNote();
    void sigNameChanged(const QString &);
    void sigColorChanged();
    void sigKillNote(Akonadi::Item::Id);

protected:
    void contextMenuEvent(QContextMenuEvent *) override;
    void showEvent(QShowEvent *) override;
    void resizeEvent(QResizeEvent *) override;
    void closeEvent(QCloseEvent *) override;
    void dropEvent(QDropEvent *) override;
    void dragEnterEvent(QDragEnterEvent *) override;

    bool event(QEvent *) override;
    bool eventFilter(QObject *, QEvent *) override;

private Q_SLOTS:
    void slotUpdateReadOnly();

    void slotSend();
    void slotMail();
    void slotPrint();
    void slotPrintPreview();
    void slotSaveAs();

    void slotSetAlarm();

    void slotPreferences();
    void slotPopupActionToDesktop(QAction *act);

    void slotApplyConfig();

    void slotUpdateShowInTaskbar();
    void slotUpdateDesktopActions();

    void slotKeepAbove();
    void slotKeepBelow();

    void slotRequestNewNote();
    void slotNoteSaved(KJob *job);
    void slotDebugAkonadiSearch();

private:
    void updateKeepAboveBelow(bool save = true);
    void buildGui();
    void createActions();
    void createNoteEditor(const QString &configFile);
    void createNoteFooter();
    void createNoteHeader();
    void prepare();

    void updateFocus();
    void updateLayout();
    void updateLabelAlignment();

    void setColor(const QColor &, const QColor &);
    void print(bool preview);
    void setDisplayDefaultValue();

private:
    void loadNoteContent(const Akonadi::Item &item);
    void updateAllAttributes();
    void saveNoteContent();
    Akonadi::Item mItem;
    QLayout *m_noteLayout = nullptr;
    QLabel *m_label = nullptr;
    QSizeGrip *m_grip = nullptr;
    KNoteButton *m_button = nullptr;
    KToolBar *m_tool = nullptr;
    KNoteEdit *m_editor = nullptr;

    QMenu *m_menu = nullptr;

    KToggleAction *m_readOnly = nullptr;

#if KDEPIM_HAVE_X11
    KSelectAction *m_toDesktop = nullptr;
#endif
    KToggleAction *m_keepAbove = nullptr;
    KToggleAction *m_keepBelow = nullptr;

    KSharedConfig::Ptr m_kwinConf;

    KNoteDisplaySettings *mDisplayAttribute = nullptr;
    bool mAllowDebugAkonadiSearch;
};

#endif
