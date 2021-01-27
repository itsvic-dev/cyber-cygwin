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

#ifndef PLACESMODEL_H
#define PLACESMODEL_H

#include <QAbstractListModel>
#include <QStandardPaths>

struct PlacesDatas {
    QString dir;
    QString iconSource;
};

class PlacesModel : public QAbstractListModel
{
    Q_OBJECT

public:
    enum Roles {
        PathRoles = Qt::UserRole + 1,
        DisplayNameRoles,
        IconSourceRoles
    };

    explicit PlacesModel(QObject *parent = nullptr);

    QString locationHome() const;
    QString locationDocuments() const;
    QString locationDownloads() const;
    QString locationMusic() const;
    QString locationPictures() const;
    QString locationVideos() const;

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QHash<int, QByteArray> roleNames() const override;

private:
    QString standardLocation(QStandardPaths::StandardLocation location) const;

private:
    QList<PlacesDatas> m_datas;
};

#endif // PLACESMODEL_H
