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

#ifndef KNOTEEDIT_H
#define KNOTEEDIT_H

#include "knotes_export.h"
#include <QTextCharFormat>
#include <QWidget>

#include <KTextEdit>
class QFont;

class QAction;
class KActionCollection;
class KFontAction;
class KFontSizeAction;
class KToggleAction;
class KNote;
namespace PimCommon {
class KActionMenuChangeCase;
}
class KNOTES_EXPORT KNoteEdit : public KTextEdit
{
    Q_OBJECT
public:
    explicit KNoteEdit(KActionCollection *actions, QWidget *parent = nullptr);
    ~KNoteEdit();

    void setNote(KNote *_note);

    void setText(const QString &text);
    QString text() const;

    void setTextFont(const QFont &font);
    void setTabStop(int tabs);
    void setAutoIndentMode(bool newmode);

    void setColor(const QColor &fg, const QColor &bg);
    void setCursorPositionFromStart(int pos);
    int cursorPositionFromStart() const;
    QMenu *mousePopupMenu() override;
public Q_SLOTS:
    void setRichText(bool);

    void textBold(bool);
    void textStrikeOut(bool);

    void slotTextColor();

    void textAlignLeft();
    void textAlignCenter();
    void textAlignRight();
    void textAlignBlock();

    void textList();

    void textSuperScript();
    void textSubScript();

    void textIncreaseIndent();
    void textDecreaseIndent();
    void setTextFontSize(int);

    void slotTextBackgroundColor();
    void slotInsertDate();

protected:
    void keyPressEvent(QKeyEvent *) override;
    void focusInEvent(QFocusEvent *) override;
    void focusOutEvent(QFocusEvent *) override;

private Q_SLOTS:
    void slotCurrentCharFormatChanged(const QTextCharFormat &);
    void slotCursorPositionChanged();
    void slotUpperCase();
    void slotLowerCase();
    void slotSentenceCase();
    void slotInsertCheckMark();
    void slotReverseCase();
private:
    void autoIndent();

    void enableRichTextActions(bool enabled);

private:
    QColor mDefaultBackgroundColor;
    QColor mDefaultForegroundColor;

    KToggleAction *m_textBold = nullptr;
    KToggleAction *m_textItalic = nullptr;
    KToggleAction *m_textUnderline = nullptr;
    KToggleAction *m_textStrikeOut = nullptr;

    KToggleAction *m_textAlignLeft = nullptr;
    KToggleAction *m_textAlignCenter = nullptr;
    KToggleAction *m_textAlignRight = nullptr;
    KToggleAction *m_textAlignBlock = nullptr;

    KToggleAction *m_textList = nullptr;
    KToggleAction *m_textSuper = nullptr;
    KToggleAction *m_textSub = nullptr;

    QAction *m_textIncreaseIndent = nullptr;
    QAction *m_textDecreaseIndent = nullptr;

    QAction *m_textColor = nullptr;
    KFontAction *m_textFont = nullptr;
    KFontSizeAction *m_textSize = nullptr;
    KNote *m_note = nullptr;
    KActionCollection *m_actions = nullptr;
    PimCommon::KActionMenuChangeCase *mChangeCaseActionMenu = nullptr;
    bool m_autoIndentMode = false;
};

#endif
