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

#ifndef FOLDERLISTMODEL_H
#define FOLDERLISTMODEL_H

#include <QAbstractListModel>
#include <QStringList>
#include <QDir>

#include "dirlister.h"
#include "dirselection.h"
#include "fileitem.h"
#include "filelauncher.h"
#include "xdgmimeapps.h"

class FolderListModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(QString path READ path NOTIFY pathChanged)
    Q_PROPERTY(DirSelection *selection READ selection CONSTANT)
    Q_PROPERTY(FileLauncher *fileLauncher READ fileLauncher CONSTANT)
    Q_PROPERTY(int count READ count NOTIFY countChanged)
    Q_PROPERTY(QStringList pathList READ pathList NOTIFY pathChanged)

public:
    enum Roles {
        FileNameRole = Qt::UserRole + 1,
        FilePathRole,
        FileBaseNameRole,
        FileSuffixRole,
        FileSizeRole,
        FileLastModifiedRole,
        FileLastReadRole,
        FileIsDirRole,
        FileUrlRole,
        FileURLRole,
        IconNameRole,
        IconSourceRole,
        CreationDateRole,
        ModifiedDateRole,
        IsSelectedRole,
        IsExecutableRole,
        IsRunnableRole,
        IsPictureRole
    };
    Q_ENUM(Roles);

    enum Status { Null, Ready, Loading };
    Q_ENUM(Status);

    explicit FolderListModel(QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QHash<int, QByteArray> roleNames() const override;

    Q_INVOKABLE QVariant get(int row, int role);

    QDir::Filters dirFilters() const;
    int count() const { return rowCount(QModelIndex()); }

    void notifyItemChanged(int index);

    QString path() const;
    Q_INVOKABLE void setPath(const QString &filePath);

    DirSelection *selection() const;
    FileLauncher *fileLauncher() const;

    QStringList pathList() const;

    Q_INVOKABLE void openIndex(int index);
    Q_INVOKABLE void runIndex(int index);
    Q_INVOKABLE void openItem(int index);
    Q_INVOKABLE void openPath(const QString &path);

    Q_INVOKABLE void openTerminal(const QString &path);

    Q_INVOKABLE void setAsWallpaper(const QString &path);

signals:
    void rowCountChanged() const;
    void countChanged() const;
    void pathChanged();
    void statusChanged();

private slots:
    void onItemAdded(FileItem *item);
    void onItemsRemove(FileItems);
    void onItemsAdded(FileItems);

private:
    FileItems m_datas;
    FileLauncher *m_fileLauncher;
    DirLister *m_dirLister;
    DirSelection *m_selection;

    MimeAppManager *m_mimeAppManager;

    QString m_currentDir;
    QStringList m_pathList;
};

#endif // FOLDERLISTMODEL_H
