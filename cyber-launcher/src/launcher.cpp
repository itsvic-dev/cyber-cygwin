/*
 * Copyright (C) 2020 CyberOS.
 *
 * Author:     revenmartin <revenmartin@gmail.com>
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

#include "launcher.h"
#include "launcheradaptor.h"
#include "iconthemeimageprovider.h"

#include <QDBusConnection>

#include <QQmlApplicationEngine>
#include <QQmlContext>

Launcher::Launcher(int &argc, char **argv)
  : QGuiApplication(argc, argv),
    m_engine(new QQmlApplicationEngine(this))
{
    new LauncherAdaptor(this);

    m_engine->addImageProvider("icontheme", new IconThemeImageProvider);
    m_engine->load(QUrl(QLatin1String("qrc:/qml/main.qml")));
}

void Launcher::show()
{
    QMetaObject::invokeMethod(m_engine->rootObjects().first(), "show");
}

void Launcher::hide()
{
    QMetaObject::invokeMethod(m_engine->rootObjects().first(), "hide");
}

void Launcher::toggle()
{
    QMetaObject::invokeMethod(m_engine->rootObjects().first(), "toggle");
}
