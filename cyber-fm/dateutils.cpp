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

#include "dateutils.h"
#include <QDateTime>

DateUtils::DateUtils(QObject *parent) : QObject(parent)
{

}

QString DateUtils::friendlyTime(const QDateTime &time, bool standalone) const
{
    QDateTime now = QDateTime::currentDateTime();
    qint64 minutes = qRound64(time.secsTo(now) / 60.0f);

    if (minutes < 1)
        return standalone ? tr("Now") : tr("now");
    else if (minutes == 1)
        return tr("1 minute ago");
    else if (minutes < 60)
        return tr("%1 minutes ago").arg(minutes);

    qint64 hours = qRound64(minutes / 60.0f);

    if (hours == 1)
        return tr("1 hour ago");
    else if (hours < 24)
        return tr("%1 hours ago").arg(hours);

    qint64 days = qRound64(hours / 24.0f);

    if (days == 1)
        return tr("1 day ago");
    else if (days <= 10)
        return tr("%1 days ago").arg(days);

    return time.toString("yyyy/MM/dd hh:mm");
}
