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

#ifndef FILELOADER_H
#define FILELOADER_H

#include <QObject>
#include <QDirIterator>
#include <QThread>
#include <QDir>
#include <QUrl>

#include "fileitem.h"

class FileLoader : public QObject
{
    Q_OBJECT

public:
    explicit FileLoader(QObject *parent = nullptr);
    ~FileLoader();

    void setPath(const QString &path, const QDir::Filters &filters);

signals:
    void finished(FileItems items);
    void itemReady(FileItem *item);
    void itemsReady(FileItems items);

private slots:
    void load(const QDir::Filters &filters);

private:
    QThread *m_thread;
    QString m_currentPath;
};

#endif // FILELOADER_H
