/*
 * Copyright (C) 2020 CyberOS Team.
 *
 * Author:     rekols <revenmartin@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "fileitem.h"
#include <QFileInfo>

QMimeDatabase FileItem::mimeDatabase;

FileItem::FileItem(const QString &filePath)
    : m_filePath(filePath)
    , m_isSelected(false)
    , m_isExecutable(false)
{
    refresh();
}

void FileItem::refresh()
{
    QFileInfo fileInfo(m_filePath);
    m_fileName = fileInfo.fileName();
    m_baseName = fileInfo.baseName();
    m_size = fileInfo.size();
    m_isDir = fileInfo.isDir();
    m_created = QDateTime();
    m_lastModified = fileInfo.lastModified();
    m_isExecutable = fileInfo.isExecutable();
}

QString FileItem::filePath() const
{
    return m_filePath;
}

QString FileItem::fileName() const
{
    return m_fileName;
}

QString FileItem::baseName() const
{
    return m_baseName;
}

quint64 FileItem::size() const
{
    return m_size;
}

QDateTime FileItem::created() const
{
    return m_created;
}

QDateTime FileItem::lastModified() const
{
    return m_lastModified;
}

QMimeType FileItem::mimeType() const
{
    return mimeDatabase.mimeTypeForFile(m_filePath);
}

bool FileItem::isDir() const
{
    return m_isDir;
}

bool FileItem::isSelected() const
{
    return m_isSelected;
}

bool FileItem::setSelection(bool selected)
{
    bool result = selected != isSelected();
    m_isSelected = selected;
    return result;
}

bool FileItem::isExecutable() const
{
    return m_isExecutable;
}

bool FileItem::isRunnable() const
{
    const QString &mimeName = mimeType().name();

    if (mimeName == "application/x-executable" ||
        mimeName == "application/x-sharedlib" ||
        mimeName == "application/x-iso9660-appimage" ||
        mimeName == "application/vnd.appimage") {
        return true;
    }

    return false;
}
