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

#include "knoteprintobject.h"
#include "attributes/notealarmattribute.h"
#include "attributes/notedisplayattribute.h"
#include "attributes/notelockattribute.h"

#include <KMime/KMimeMessage>

#include <QLocale>

KNotePrintObject::KNotePrintObject(const Akonadi::Item &item, QObject *parent)
    : QObject(parent)
    , mItem(item)
{
}

KNotePrintObject::~KNotePrintObject()
{
}

QString KNotePrintObject::description() const
{
    KMime::Message::Ptr noteMessage = mItem.payload<KMime::Message::Ptr>();
    if (noteMessage->contentType()->isHTMLText()) {
        return noteMessage->mainBodyPart()->decodedText();
    } else {
        return noteMessage->mainBodyPart()->decodedText().replace(QLatin1Char('\n'), QStringLiteral("<br>"));
    }
}

QString KNotePrintObject::name() const
{
    KMime::Message::Ptr noteMessage = mItem.payload<KMime::Message::Ptr>();
    const KMime::Headers::Subject *const subject = noteMessage ? noteMessage->subject(false) : nullptr;
    return subject ? subject->asUnicodeString() : QString();
}

QString KNotePrintObject::currentDateTime() const
{
    const QDateTime now = QDateTime::currentDateTime();
    return QLocale().toString((now), QLocale::ShortFormat);
}

bool KNotePrintObject::hasAlarm() const
{
    return mItem.hasAttribute<NoteShared::NoteAlarmAttribute>();
}

QString KNotePrintObject::alarm() const
{
    NoteShared::NoteAlarmAttribute *attr = mItem.attribute<NoteShared::NoteAlarmAttribute>();
    if (attr) {
        return QLocale().toString(attr->dateTime(), QLocale::LongFormat);
    }
    return QString();
}

bool KNotePrintObject::isLock() const
{
    return mItem.hasAttribute<NoteShared::NoteLockAttribute>();
}

QString KNotePrintObject::backgroundColorName() const
{
    if (mItem.hasAttribute<NoteShared::NoteDisplayAttribute>()) {
        return mItem.attribute<NoteShared::NoteDisplayAttribute>()->backgroundColor().name();
    }
    return QString();
}
