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

#include "placesmodel.h"
#include <QDir>

PlacesModel::PlacesModel(QObject *parent)
    : QAbstractListModel(parent)
{
    if (QFile::exists(locationHome())) {
        PlacesDatas data;
        data.dir = locationHome();
        data.iconSource = "qrc:/images/folder-home.svg";
        m_datas.append(data);
    }

    if (QFile::exists(locationDocuments())) {
        PlacesDatas data;
        data.dir = locationDocuments();
        data.iconSource = "qrc:/images/folder-document.svg";
        m_datas.append(data);
    }

    if (QFile::exists(locationDownloads())) {
        PlacesDatas data;
        data.dir = locationDownloads();
        data.iconSource = "qrc:/images/folder-download.svg";
        m_datas.append(data);
    }

    if (QFile::exists(locationMusic())) {
        PlacesDatas data;
        data.dir = locationMusic();
        data.iconSource = "qrc:/images/folder-music.svg";
        m_datas.append(data);
    }

    if (QFile::exists(locationPictures())) {
        PlacesDatas data;
        data.dir = locationPictures();
        data.iconSource = "qrc:/images/folder-picture.svg";
        m_datas.append(data);
    }

    if (QFile::exists(locationVideos())) {
        PlacesDatas data;
        data.dir = locationVideos();
        data.iconSource = "qrc:/images/folder-video.svg";
        m_datas.append(data);
    }
}

QString PlacesModel::locationHome() const
{
    return standardLocation(QStandardPaths::HomeLocation);
}

QString PlacesModel::locationDocuments() const
{
    return standardLocation(QStandardPaths::DocumentsLocation);
}

QString PlacesModel::locationDownloads() const
{
    return standardLocation(QStandardPaths::DownloadLocation);
}

QString PlacesModel::locationMusic() const
{
    return standardLocation(QStandardPaths::MusicLocation);
}

QString PlacesModel::locationPictures() const
{
    return standardLocation(QStandardPaths::PicturesLocation);
}

QString PlacesModel::locationVideos() const
{
    return standardLocation(QStandardPaths::MoviesLocation);
}

int PlacesModel::rowCount(const QModelIndex &) const
{
    return m_datas.count();
}

QVariant PlacesModel::data(const QModelIndex &index, int roles) const
{
    PlacesDatas data = m_datas.at(index.row());

    switch (roles) {
    case PathRoles:
        return data.dir;
        break;
    case DisplayNameRoles:
        return QDir(data.dir).dirName();
        break;
    case IconSourceRoles:
        return data.iconSource;
        break;
    }

    return QVariant();
}

QHash<int, QByteArray> PlacesModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles.insert(PlacesModel::PathRoles, "path");
    roles.insert(PlacesModel::DisplayNameRoles, "displayName");
    roles.insert(PlacesModel::IconSourceRoles, "iconSource");
    return roles;
}

QString PlacesModel::standardLocation(QStandardPaths::StandardLocation location) const
{
    QStringList locations = QStandardPaths::standardLocations(location);
    QString standardLocation = "";

    foreach (const QString &location, locations) {
        // We always return the first location or an empty string
        // The frontend should check out that it exists
        if (QDir(location).exists()) {
            standardLocation = location;
            break;
        }
    }

    return standardLocation;
}
