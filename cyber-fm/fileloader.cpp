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

#include "fileloader.h"
#include <QDebug>

FileLoader::FileLoader(QObject *parent)
    : QObject(parent)
    , m_thread(new QThread)
{
    this->moveToThread(m_thread);
    connect(m_thread, &QThread::finished, m_thread, &QObject::deleteLater);
    m_thread->start();
}

FileLoader::~FileLoader()
{
    m_thread->quit();
    m_thread->wait();
}

void FileLoader::setPath(const QString &path, const QDir::Filters &filters)
{
    if (path == m_currentPath)
        return;

    if (!QDir(path).exists())
        return;

    m_currentPath = path;

    load(filters);
}

void FileLoader::load(const QDir::Filters &filters)
{
    FileItems list;
    QDir dir(m_currentPath, QString(), QDir::Name | QDir::DirsFirst);
    const QFileInfoList fileInfoList = dir.entryInfoList(QStringList(), filters, QDir::Name | QDir::DirsFirst);

    if (!fileInfoList.isEmpty()) {
        list.reserve(fileInfoList.size());

        for (const QFileInfo &info : fileInfoList) {
            FileItem *item = new FileItem(info.filePath());
            list.append(item);
            emit itemReady(item);
        }
    }

    emit itemsReady(list);
    emit finished(list);
}
