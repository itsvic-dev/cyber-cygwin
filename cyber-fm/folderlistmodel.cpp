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

#include "folderlistmodel.h"
#include <QDBusInterface>
#include <QDesktopServices>
#include <QDebug>

FolderListModel::FolderListModel(QObject *parent)
    : QAbstractListModel(parent)
    , m_fileLauncher(FileLauncher::self())
    , m_dirLister(new DirLister(this, &m_datas))
    , m_selection(new DirSelection(this, &m_datas))
    , m_mimeAppManager(new MimeAppManager)
{
    // Init
    qRegisterMetaType<FileItems>("QList<FileItem>");
    qRegisterMetaType<FolderListModel::Status>("FolderListModel::Status");

    connect(m_dirLister, &DirLister::itemReady, this, &FolderListModel::onItemAdded);
    connect(m_dirLister, &DirLister::itemsRemove, this, &FolderListModel::onItemsRemove);
    connect(m_dirLister, &DirLister::itemsAdded, this, &FolderListModel::onItemsAdded);

    connect(this, &FolderListModel::rowCountChanged, this, &FolderListModel::countChanged);

    setPath(QDir::homePath());
}

int FolderListModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);

    return m_datas.size();
}

QModelIndex FolderListModel::index(int row, int, const QModelIndex &) const
{
    return createIndex(row, 0);
}

QVariant FolderListModel::data(const QModelIndex &index, int role) const
{
    FileItem *item = m_datas.at(index.row());

    switch (role) {
    case FileNameRole:
        return item->fileName();
        break;
    case FilePathRole:
        return item->filePath();
        break;
    case FileBaseNameRole:
        return item->baseName();
        break;
    case FileSizeRole:
        return item->size();
        break;
    case FileIsDirRole:
        return item->isDir();
        break;
    case IconNameRole: {
        return QString("image://icontheme/%1").arg(item->mimeType().iconName());
    }
        break;
    case IconSourceRole: {
        if (item->mimeType().name() == "image/svg+xml")
            return QString("file://%1").arg(item->filePath());

        if (item->mimeType().name().startsWith("image/"))
            return QString("file://%1").arg(item->filePath());

        return QString();
    }
        break;
    case CreationDateRole:
        return item->created();
        break;
    case ModifiedDateRole:
        return item->lastModified();
        break;
    case IsSelectedRole:
        return item->isSelected();
        break;
    case IsExecutableRole:
        return item->isExecutable();
        break;
    case IsRunnableRole:
        return item->isRunnable();
        break;
    case IsPictureRole:
        return item->mimeType().name().startsWith("image/");
        break;
    default:
        break;
    }

    return QVariant();
}

QHash<int, QByteArray> FolderListModel::roleNames() const
{
    QHash<int, QByteArray> roleNames;
    roleNames[FileNameRole] = "fileName";
    roleNames[FilePathRole] = "filePath";
    roleNames[FileBaseNameRole] = "fileBaseName";
    roleNames[FileSuffixRole] = "fileSuffix";
    roleNames[FileSizeRole] = "fileSize";
    roleNames[FileLastModifiedRole] = "fileModified";
    roleNames[FileLastReadRole] = "fileAccessed";
    roleNames[FileIsDirRole] = "fileIsDir";
    roleNames[FileUrlRole] = "fileUrl";
    roleNames[FileURLRole] = "fileURL";
    roleNames[IconNameRole] = "iconName";
    roleNames[IconSourceRole] = "iconSource";
    roleNames[CreationDateRole] = "creationDate";
    roleNames[ModifiedDateRole] = "modifiedDate";
    roleNames[IsSelectedRole] = "isSelected";
    roleNames[IsExecutableRole] = "isExecutable";
    roleNames[IsRunnableRole] = "isRunnable";
    roleNames[IsPictureRole] = "isPicture";
    return roleNames;
}

QVariant FolderListModel::get(int row, int role)
{
    return data(index(row, 0), role);
}

QDir::Filters FolderListModel::dirFilters() const
{
    QDir::Filters filter;
    // show files
    filter = filter | QDir::Files;
    // show dirs
    filter = filter | QDir::AllDirs | QDir::Drives;
    // showDotAndDotDot
    filter = filter | QDir::NoDot | QDir::NoDotDot;

    return filter;
}

void FolderListModel::notifyItemChanged(int index)
{
    QModelIndex idx = QAbstractListModel::index(index, 0);
    emit dataChanged(idx, idx);
}

QString FolderListModel::path() const
{
    return m_currentDir;
}

void FolderListModel::setPath(const QString &filePath)
{
    if (filePath == m_currentDir)
        return;

    QFileInfo info(filePath);

    if (!info.exists() || !info.isDir()) {
        return;
    }

    // Handle path list
    m_pathList.clear();
    QString _path = filePath + "/";
    // while (_path.endsWith("/"))
    //     _path.chop(1);

    int count = _path.count("/");

    for (int i = 0; i < count; ++i) {
        _path = QString(_path).left(_path.lastIndexOf("/"));

        QString dirName = QString(_path).right(_path.length() - _path.lastIndexOf("/") - 1);

        if (dirName.isEmpty())
            continue;

        m_pathList << dirName;
    }

    std::reverse(m_pathList.begin(), m_pathList.end());

    m_currentDir = filePath;

    beginResetModel();
    m_datas.clear();
    endResetModel();

    m_dirLister->setPath(filePath);

    emit pathChanged();
    emit rowCountChanged();
}

DirSelection *FolderListModel::selection() const
{
    return m_selection;
}

FileLauncher *FolderListModel::fileLauncher() const
{
    return m_fileLauncher;
}

QStringList FolderListModel::pathList() const
{
    return m_pathList;
}

void FolderListModel::openIndex(int index)
{
    FileItem *item = m_datas.at(index);

    // Open Directory.
    if (item->isDir()) {
        setPath(item->filePath());
    } else {
        if (item->isRunnable()) {
            return;
        }
    }
}

void FolderListModel::runIndex(int index)
{
    FileItem *item = m_datas.at(index);

    if (!item->isRunnable())
        return;

    QFileInfo fileInfo(item->filePath());
    if (!fileInfo.isExecutable()) {
        QFile file(item->filePath());
        file.setPermissions(file.permissions() | QFile::ExeOwner | QFile::ExeUser | QFile::ExeGroup | QFile::ExeOther);
    }

    m_fileLauncher->launchExecutable(item->filePath());
}

void FolderListModel::openItem(int index)
{
    FileItem *item = m_datas.at(index);

    QString defaultAppDesktopFile = m_mimeAppManager->getDefaultAppByMimeType(item->mimeType());
    // If no default application is found,
    // look for the first one of the frequently used applications.
    if (defaultAppDesktopFile.isEmpty()) {
        QStringList recommendApps = m_mimeAppManager->getRecommendedAppsByMimeType(item->mimeType());
        if (recommendApps.count() > 0) {
            defaultAppDesktopFile = recommendApps.first();
        }
    }

    if (!defaultAppDesktopFile.isEmpty()) {
        m_fileLauncher->launchApp(defaultAppDesktopFile, item->filePath());
        return;
    }

    QDesktopServices::openUrl(QUrl::fromLocalFile(item->filePath()));
}

void FolderListModel::openPath(const QString &path)
{
    // Open from pathbar item.
    QString newPath = m_currentDir.left(m_currentDir.indexOf(path) + path.length());
    setPath(newPath);
}

void FolderListModel::openTerminal(const QString &path)
{
    m_mimeAppManager->launchTerminal(path);
}

void FolderListModel::setAsWallpaper(const QString &path)
{
    QDBusInterface iface("org.cyber.Settings", "/Theme",
                         "org.cyber.Theme",
                         QDBusConnection::sessionBus(), this);
    if (iface.isValid())
        iface.call("setWallpaper", path);
}

void FolderListModel::onItemAdded(FileItem *item)
{
    beginInsertRows(QModelIndex(), m_datas.count(), m_datas.count());
    m_datas.append(item);
    endInsertRows();

    emit rowCountChanged();
}

void FolderListModel::onItemsRemove(FileItems items)
{
    for (FileItem *item : items) {
        int index = m_datas.indexOf(item);
        if (index != -1) {
            beginRemoveRows(QModelIndex(), index, index);
            m_datas.removeAt(index);
            endRemoveRows();
        }
    }
}

void FolderListModel::onItemsAdded(FileItems items)
{
    for (FileItem *item : items) {
        onItemAdded(item);
    }
}
