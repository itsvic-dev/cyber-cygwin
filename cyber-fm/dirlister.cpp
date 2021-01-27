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

#include "dirlister.h"
#include "folderlistmodel.h"

#include <QFileSystemWatcher>
#include <QDebug>

DirLister::DirLister(FolderListModel *model, FileItems *fileItems, QObject *parent)
    : QObject(parent)
    , m_fileWatcher(new QFileSystemWatcher(this))
    , m_model(model)
    , m_fileItems(fileItems)
    , m_fileLoader(new FileLoader)
    , m_checking(false)
{
    connect(m_fileWatcher, &QFileSystemWatcher::directoryChanged, this, &DirLister::onDirectoryChanged);
    connect(m_fileWatcher, &QFileSystemWatcher::fileChanged, this, &DirLister::onFileChanged);

    connect(m_fileLoader, &FileLoader::itemReady, this, &DirLister::onItemReady);
}

void DirLister::clear()
{
    if (!m_fileWatcher->files().isEmpty())
        m_fileWatcher->removePaths(m_fileWatcher->files());

    if (!m_fileWatcher->directories().isEmpty())
        m_fileWatcher->removePaths(m_fileWatcher->directories());
}

void DirLister::setPath(const QString &path)
{
    if (path == m_currentPath)
        return;

    m_currentPath = path;

    clear();
    m_fileWatcher->addPath(path);
    m_fileLoader->setPath(m_currentPath, m_model->dirFilters());
}

bool DirLister::contains(const QString &path)
{
    for (int i = 0; i < m_fileItems->size(); ++i) {
        FileItem *item = m_fileItems->at(i);
        if (item->filePath() == path)
            return true;
    }

    return false;
}

void DirLister::onDirectoryChanged(const QString &path)
{
    Q_UNUSED(path);

    if (m_checking)
        return;

    m_checking = true;

    FileItems removedItems;

    for (int i = 0; i < m_fileItems->size(); ++i) {
        const QString &filePath = m_fileItems->at(i)->filePath();

        if (!QFileInfo::exists(filePath)) {
            m_fileWatcher->removePath(filePath);
            removedItems.append(m_fileItems->at(i));
        }
    }

    if (!removedItems.isEmpty())
        emit itemsRemove(removedItems);

    FileLoader *checkLoader = new FileLoader;

    connect(checkLoader, &FileLoader::itemsReady, this, [=] (FileItems items) {
        for (FileItem *i : items) {
            if (!contains(i->filePath())) {
                onItemReady(i);
                m_fileWatcher->addPath(i->filePath());
            }
        }

        checkLoader->deleteLater();
        m_checking = false;
    });

    connect(checkLoader, &FileLoader::finished, this, [=] {
        checkLoader->deleteLater();
        m_checking = false;
    });

    checkLoader->setPath(m_currentPath, m_model->dirFilters());
}

void DirLister::onFileChanged(const QString &path)
{
    for (int i = 0; i <= m_fileItems->size(); ++i) {
        FileItem *item = m_fileItems->at(i);
        if (item->filePath() == path) {
            item->refresh();
            emit itemChanged(item);
            break;
        }
    }
}

void DirLister::onItemReady(FileItem *item)
{
    m_fileWatcher->addPath(item->filePath());

    emit itemReady(item);
}
