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

#ifndef FILEITEM_H
#define FILEITEM_H

#include <QObject>
#include <QMimeDatabase>
#include <QMimeType>
#include <QDateTime>

class FileItem
{
public:
    explicit FileItem(const QString &filePath);

    void refresh();

    QString filePath() const;
    QString fileName() const;
    QString baseName() const;
    quint64 size() const;

    QDateTime created() const;
    QDateTime lastModified() const;

    QMimeType mimeType() const;

    bool isDir() const;

    bool isSelected() const;
    bool setSelection(bool selected);

    bool isExecutable() const;
    bool isRunnable() const;

    inline bool operator !=(const FileItem &fileItem) const {
        return !operator==(fileItem);
    }

    inline bool operator ==(const FileItem &fileItem) const {
        return (m_filePath == fileItem.m_filePath) && m_isDir == fileItem.m_isDir;
    }

private:
    QString m_filePath;
    QString m_fileName;
    QString m_baseName;
    quint64 m_size;

    QDateTime m_created;
    QDateTime m_lastModified;

    static QMimeDatabase mimeDatabase;

    bool m_isDir;
    bool m_isSelected;
    bool m_isExecutable;
};

typedef QList<FileItem *> FileItems;

#endif // FILEITEM_H
