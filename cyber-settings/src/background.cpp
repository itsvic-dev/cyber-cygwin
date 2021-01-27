#include "background.h"
#include <QtConcurrent>

static QVariantList getBackgroundPaths()
{
    QVariantList list;
    QDirIterator it("/usr/share/backgrounds", QStringList() << "*.jpg" << "*.png", QDir::Files, QDirIterator::Subdirectories);
    while (it.hasNext()) {
        QString bg = it.next();
        list.append(QVariant(bg));
    }
    return list;
}

Background::Background(QObject *parent)
    : QObject(parent)
{
    QDBusInterface iface("org.cyber.Settings",
                         "/Theme",
                         "org.cyber.Theme",
                         QDBusConnection::sessionBus(), this);
    if (iface.isValid()) {
        m_currentPath = iface.property("wallpaper").toString();
    }
}

QVariantList Background::backgrounds()
{
    QFuture<QVariantList> future = QtConcurrent::run(&getBackgroundPaths);
    QVariantList list = future.result();
    return list;
}

QString Background::currentBackgroundPath()
{
    return m_currentPath;
}

void Background::setBackground(QString path)
{
    if (m_currentPath != path) {
        m_currentPath = path;

        QDBusInterface iface("org.cyber.Settings",
                             "/Theme",
                             "org.cyber.Theme",
                             QDBusConnection::sessionBus(), this);
        if (iface.isValid()) {
            iface.call("setWallpaper", path);
            emit backgroundChanged();
        }
    }
}
