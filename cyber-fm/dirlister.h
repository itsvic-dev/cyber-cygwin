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

#ifndef DIRLISTER_H
#define DIRLISTER_H

#include <QObject>
#include "fileitem.h"
#include "fileloader.h"

class QFileSystemWatcher;
class FolderListModel;
class DirLister : public QObject
{
    Q_OBJECT

public:
    explicit DirLister(FolderListModel *model, FileItems *fileItems, QObject *parent = nullptr);

    void clear();
    void setPath(const QString &path);

    bool contains(const QString &path);

signals:
    void itemReady(FileItem *);
    void itemRemove(FileItem *);
    void itemsRemove(FileItems);
    void itemsAdded(FileItems);
    void itemChanged(FileItem *);

private slots:
    void onDirectoryChanged(const QString &path);
    void onFileChanged(const QString &path);

    void onItemReady(FileItem *);

private:
    QFileSystemWatcher *m_fileWatcher;
    FolderListModel *m_model;
    FileItems *m_fileItems;
    FileLoader *m_fileLoader;
    QString m_currentPath;
    bool m_checking;
};

#endif // DIRLISTER_H
