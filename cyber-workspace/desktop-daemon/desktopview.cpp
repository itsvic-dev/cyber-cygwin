#include "desktopview.h"

#include <QGuiApplication>
#include <QScreen>

#include <KWindowSystem>

DesktopView::DesktopView(QQuickView *parent)
    : QQuickView(parent)
{
    setFlags(Qt::Window | Qt::FramelessWindowHint);
    setTitle(tr("Desktop"));

    KWindowSystem::setType(winId(), NET::Desktop);
    KWindowSystem::setState(winId(), NET::KeepBelow);

    setScreen(qGuiApp->primaryScreen());
    setResizeMode(QQuickView::SizeRootObjectToView);
    setSource(QStringLiteral("qrc:/Desktop.qml"));
    screenGeometryChanged();

    connect(qGuiApp->primaryScreen(), &QScreen::virtualGeometryChanged, this, &DesktopView::screenGeometryChanged);
    connect(qGuiApp->primaryScreen(), &QScreen::geometryChanged, this, &DesktopView::screenGeometryChanged);
}

void DesktopView::screenGeometryChanged()
{
    setGeometry(qGuiApp->primaryScreen()->geometry());
}
