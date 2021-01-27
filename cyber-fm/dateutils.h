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

#ifndef DATEUTILS_H
#define DATEUTILS_H

#include <QObject>

class DateUtils : public QObject
{
    Q_OBJECT

public:
    explicit DateUtils(QObject *parent = nullptr);

    Q_INVOKABLE QString friendlyTime(const QDateTime &time, bool standalone = true) const;
};

#endif // DATEUTILS_H
