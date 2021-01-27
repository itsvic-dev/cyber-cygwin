/*************************************************************************
 * Copyright (C) 2014 by Hugo Pereira Da Costa <hugo.pereira@free.fr>    *
 * Copyright (C) 2018, 2020 by Vlad Zahorodnii <vlad.zahorodnii@kde.org> *
 * Copyright (C) 2020, 2020 by Reven Martin <revenmartin@gmail.com>      *
 *                                                                       *
 * This program is free software; you can redistribute it and/or modify  *
 * it under the terms of the GNU General Public License as published by  *
 * the Free Software Foundation; either version 2 of the License, or     *
 * (at your option) any later version.                                   *
 *                                                                       *
 * This program is distributed in the hope that it will be useful,       *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 * GNU General Public License for more details.                          *
 *                                                                       *
 * You should have received a copy of the GNU General Public License     *
 * along with this program; if not, write to the                         *
 * Free Software Foundation, Inc.,                                       *
 * 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA .        *
 *************************************************************************/

#include "shadowhelper.h"
#include "boxshadowrenderer.h"

#include <QDockWidget>
#include <QEvent>
#include <QApplication>
#include <QMenu>
#include <QPainter>
#include <QPixmap>
#include <QPlatformSurfaceEvent>
#include <QToolBar>
#include <QTextStream>

#include <KWindowSystem>

const char netWMSkipShadow[] = "_CYBER_NET_WM_SKIP_SHADOW";
const char netWMForceShadow[] = "_CYBER_NET_WM_FORCE_SHADOW";
const char netWMFrameRadius[] = "_CYBER_NET_WM_FRAME_RADIUS";


ShadowHelper::ShadowHelper(QObject * parent)
    : QObject(parent),
      m_frameRadius(5)
{
}

ShadowHelper::~ShadowHelper()
{
}

bool ShadowHelper::registerWidget(QWidget *widget, bool force)
{
    return true;
}

void ShadowHelper::unregisterWidget(QWidget *widget)
{
}

bool ShadowHelper::eventFilter(QObject *object, QEvent *event)
{
}

void ShadowHelper::objectDeleted(QObject *object)
{
}

bool ShadowHelper::isMenu(QWidget *widget) const
{
}

bool ShadowHelper::isToolTip(QWidget *widget) const
{
}

bool ShadowHelper::isDockWidget(QWidget *widget) const
{
}

bool ShadowHelper::isToolBar(QWidget *widget) const
{
}

bool ShadowHelper::acceptWidget(QWidget *widget) const
{
}

void ShadowHelper::installShadows(QWidget *widget, TileSet shadowTiles)
{
}

QMargins ShadowHelper::shadowMargins(QWidget *widget, TileSet shadowTiles) const
{
}

void ShadowHelper::uninstallShadows(QWidget *widget)
{
}
