#include "mainwindow.h"
#include "iconthemeimageprovider.h"
#include "processprovider.h"
#include "windowcontrol.h"

#include <QApplication>
#include <QScreen>
#include <QAction>
#include <QPainter>
#include <QImage>
#include <QRegion>

#include <QQmlContext>
#include <QQmlProperty>
#include <QQuickItem>
#include <QMetaEnum>

#include <NETWM>
#include <KWindowSystem>
#include <KWindowEffects>

MainWindow::MainWindow(QQuickView *parent)
    : QQuickView(parent)
    , m_battery(new Battery)
    , m_volumeManager(VolumeManager::self())
    , m_volumeControlWindow(new VolumeControlWindow)
    , m_statusNotifierModel(new StatusNotifierModel)
{
    setDefaultAlphaBuffer(true);
    setColor(Qt::transparent);

    setFlags(Qt::FramelessWindowHint | Qt::WindowDoesNotAcceptFocus);
    KWindowSystem::setState(winId(), NET::SkipTaskbar | NET::SkipPager);
    KWindowSystem::setOnDesktop(winId(), NET::OnAllDesktops);
    KWindowSystem::setType(winId(), NET::Dock);

    rootContext()->setContextProperty("Battery", m_battery);
    rootContext()->setContextProperty("Volume", m_volumeManager);
    rootContext()->setContextProperty("VolumeControlWindow", m_volumeControlWindow);
    rootContext()->setContextProperty("StatusNotifierModel", m_statusNotifierModel);

    engine()->addImageProvider("icontheme", new IconThemeImageProvider);
    engine()->rootContext()->setContextProperty("Process", new ProcessProvider);
    engine()->rootContext()->setContextProperty("WindowControl", new WindowControl);

    setResizeMode(QQuickView::SizeRootObjectToView);
    setClearBeforeRendering(true);
    setScreen(qApp->primaryScreen());
    setSource(QUrl(QStringLiteral("qrc:/qml/main.qml")));

    resizeWindow();

    connect(qApp->primaryScreen(), &QScreen::virtualGeometryChanged, this, &MainWindow::resizeWindow);
    connect(qApp->primaryScreen(), &QScreen::geometryChanged, this, &MainWindow::resizeWindow);
}

void MainWindow::resizeWindow()
{
    QRect screenGeometry = qApp->primaryScreen()->geometry();
    QRect windowGeometry(screenGeometry.x(),
                         screenGeometry.y(),
                         screenGeometry.width(),
                         30);

    setGeometry(windowGeometry);
    updateViewStruts();

    KWindowEffects::enableBlurBehind(winId(), true, geometry());

    setVisible(true);
}

void MainWindow::updateViewStruts()
{
    const QRect windowRect = geometry();
    NETExtendedStrut strut;

    strut.top_width = windowRect.height();
    strut.top_start = x();
    strut.top_end = x() + windowRect.width();

    KWindowSystem::setExtendedStrut(winId(),
                                 strut.left_width,
                                 strut.left_start,
                                 strut.left_end,
                                 strut.right_width,
                                 strut.right_start,
                                 strut.right_end,
                                 strut.top_width,
                                 strut.top_start,
                                 strut.top_end,
                                 strut.bottom_width,
                                 strut.bottom_start,
                                 strut.bottom_end);
}
