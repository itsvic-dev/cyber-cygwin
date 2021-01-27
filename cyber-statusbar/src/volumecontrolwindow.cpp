#include "volumecontrolwindow.h"
#include <QQmlContext>
#include <QDebug>

#include <KWindowSystem>

VolumeControlWindow::VolumeControlWindow(QQuickView *parent)
    : QQuickView(parent)
    , m_volumeManager(VolumeManager::self())
{
    setFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
    setResizeMode(QQuickView::SizeViewToRootObject);
    setClearBeforeRendering(true);
    setDefaultAlphaBuffer(true);
    setColor(Qt::transparent);
    rootContext()->setContextProperty("Volume", m_volumeManager);
    setSource(QUrl(QStringLiteral("qrc:/qml/VolumeControl.qml")));
    setVisible(false);

    connect(this, &QQuickView::activeChanged, this, &VolumeControlWindow::onActiveChanged);
}

void VolumeControlWindow::popup(const QPointF point)
{
    if (isVisible()) {
        setVisible(false);
        return;
    }

    setVisible(true);
    setX(point.x());
    setY(point.y() - height());
}

void VolumeControlWindow::hide()
{
    setVisible(false);
}

void VolumeControlWindow::showEvent(QShowEvent *event)
{
    KWindowSystem::setState(winId(), NET::SkipTaskbar | NET::SkipPager | NET::SkipSwitcher);

    QQuickView::showEvent(event);
}

void VolumeControlWindow::onActiveChanged()
{
    if (!isActive())
        hide();
}
