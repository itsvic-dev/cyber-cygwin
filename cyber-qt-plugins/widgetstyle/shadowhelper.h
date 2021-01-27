/*************************************************************************
 * Copyright (C) 2014 by Hugo Pereira Da Costa <hugo.pereira@free.fr>    *
 * Copyright (C) 2020 by Vlad Zahorodnii <vlad.zahorodnii@kde.org>       *
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

#ifndef SHADOWHELPER_H
#define SHADOWHELPER_H

#include "tileset.h"
//#include <KWindowShadow>

#include <QObject>
#include <QPointer>
#include <QMap>
#include <QMargins>
#include <QSet>

//* handle shadow pixmaps passed to window manager via X property
class ShadowHelper: public QObject
{
    Q_OBJECT

public:
    //* constructor
    ShadowHelper(QObject *);

    //* destructor
    ~ShadowHelper() override;

    //* register widget
    bool registerWidget(QWidget *, bool force = false);

    //* unregister widget
    void unregisterWidget(QWidget *);

    //* event filter
    bool eventFilter(QObject *, QEvent *) override;

    void setFrameRadius(qreal radius) { m_frameRadius = radius; }

protected Q_SLOTS:
    //* unregister widget
    void objectDeleted(QObject *);

protected:
    //* true if widget is a menu
    bool isMenu(QWidget *) const;

    //* true if widget is a tooltip
    bool isToolTip(QWidget *) const;

    //* dock widget
    bool isDockWidget(QWidget *) const;

    //* toolbar
    bool isToolBar(QWidget *) const;

    //* accept widget
    bool acceptWidget(QWidget *) const;

    //* installs shadow on given widget in a platform independent way
    // void installShadows( QWidget * );

    void installShadows(QWidget *widget, TileSet shadowTiles);

    //* uninstalls shadow on given widget in a platform independent way
    void uninstallShadows(QWidget *);

    //* gets the shadow margins for the given widget
    QMargins shadowMargins(QWidget*, TileSet) const;

private:
    //* registered widgets
    QSet<QWidget *> m_widgets;

    qreal m_frameRadius;

    //* number of tiles
    enum { numTiles = 8 };
};

#endif
