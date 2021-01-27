#include "mainwindow.h"
#include "iconthemeimageprovider.h"
#include "processprovider.h"

#include <QGuiApplication>
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

MainWindow::MainWindow(QQuickView *parent)
    : QQuickView(parent)
    , m_settings(DockSettings::self())
    , m_appModel(new ApplicationModel)
    , m_resizeAnimation(new QVariantAnimation(this))
{
    m_resizeAnimation->setDuration(250);
    m_resizeAnimation->setEasingCurve(QEasingCurve::InOutQuad);

    setDefaultAlphaBuffer(true);
    setColor(Qt::transparent);

    setFlags(Qt::FramelessWindowHint | Qt::WindowDoesNotAcceptFocus);
    KWindowSystem::setState(winId(), NET::SkipTaskbar | NET::SkipPager);
    KWindowSystem::setOnDesktop(winId(), NET::OnAllDesktops);
    KWindowSystem::setType(winId(), NET::Dock);

    qmlRegisterType<DockSettings>("org.cyber.Dock", 1, 0, "DockSettings");
    engine()->rootContext()->setContextProperty("appModel", m_appModel);
    engine()->rootContext()->setContextProperty("process", new ProcessProvider);
    engine()->rootContext()->setContextProperty("Settings", m_settings);

    setResizeMode(QQuickView::SizeRootObjectToView);
    setClearBeforeRendering(true);
    setScreen(qApp->primaryScreen());
    setSource(QUrl(QStringLiteral("qrc:/qml/main.qml")));
    resizeWindow();

    connect(qApp->primaryScreen(), &QScreen::virtualGeometryChanged, this, &MainWindow::resizeWindow, Qt::QueuedConnection);
    connect(qApp->primaryScreen(), &QScreen::geometryChanged, this, &MainWindow::resizeWindow, Qt::QueuedConnection);

    connect(m_appModel, &ApplicationModel::countChanged, this, &MainWindow::animationResizing);
    connect(m_settings, &DockSettings::directionChanged, this, &MainWindow::positionAnimationResizing);
    connect(m_settings, &DockSettings::iconSizeChanged, this, &MainWindow::animationResizing);

    connect(m_resizeAnimation, &QVariantAnimation::valueChanged, this, &MainWindow::onAnimationValueChanged);
    connect(m_resizeAnimation, &QVariantAnimation::finished, this, &MainWindow::updateViewStruts);
}

QRect MainWindow::windowRect() const
{
    const QRect screenGeometry = qApp->primaryScreen()->geometry();

    // Launcher and Trash
    const int fixedItemCount = 2;

    const int maxLength = (m_settings->direction() == DockSettings::Left) ?
                           screenGeometry.height() - DockSettings::self()->statusBarHeight() - m_settings->edgeMargins() :
                           screenGeometry.width() - m_settings->edgeMargins();
    int calcIconSize = m_settings->iconSize();
    int allCount = m_appModel->rowCount() + fixedItemCount;
    int calcLength = allCount * calcIconSize;

    // Cannot be greater than the screen length.
    while (1) {
        if (calcLength < maxLength)
            break;

        calcIconSize -= 1;
        calcLength = allCount * calcIconSize;
    }

    QSize newSize(0, 0);
    QPoint position(0, 0);

    switch (m_settings->direction()) {
    case DockSettings::Left:
        newSize = QSize(calcIconSize, calcLength);
        position = { screenGeometry.x() + DockSettings::self()->edgeMargins() / 2,
                     (screenGeometry.height() + DockSettings::self()->statusBarHeight() - newSize.height()) / 2
                   };
        break;
    case DockSettings::Bottom:
        newSize = QSize(calcLength, calcIconSize);
        position = { (screenGeometry.width() - newSize.width()) / 2,
                     screenGeometry.y() + screenGeometry.height() - newSize.height()
                     - DockSettings::self()->edgeMargins() / 2
                   };
        break;
    default:
        break;
    }

    return QRect(position, newSize);
}

void MainWindow::resizeWindow()
{
    setGeometry(windowRect());
    updateBlurRegion();
    updateViewStruts();
    setVisible(true);
}

void MainWindow::animationResizing()
{
    m_resizeAnimation->setStartValue(this->geometry());
    m_resizeAnimation->setEndValue(windowRect());
    m_resizeAnimation->setDuration(250);
    m_resizeAnimation->start();
}

void MainWindow::positionAnimationResizing()
{
    const QRect screenGeometry = qApp->primaryScreen()->geometry();
    QRect rect = windowRect();

    switch (m_settings->direction()) {
    case DockSettings::Left:
        setGeometry(QRect(screenGeometry.x() - rect.width(), rect.y(), rect.width(), rect.height()));
        m_resizeAnimation->setStartValue(QRect(screenGeometry.x() - rect.width(), rect.y(), rect.width(), rect.height()));
        break;
    case DockSettings::Bottom:
        setGeometry(QRect(rect.x(), screenGeometry.height() + rect.height(), rect.width(), rect.height()));
        m_resizeAnimation->setStartValue(QRect(rect.x(), screenGeometry.height() + rect.height(), rect.width(), rect.height()));
        break;
    default:
        break;
    }

    m_resizeAnimation->setEndValue(windowRect());
    m_resizeAnimation->setDuration(300);
    m_resizeAnimation->start();
}

void MainWindow::updateBlurRegion()
{
    const QRect rect { 0, 0, size().width(), size().height() };
    int radius = m_settings->direction() == DockSettings::Left ? rect.width() * 0.3
                                                               : rect.height() * 0.3;
    XWindowInterface::instance()->enableBlurBehind(this, true, cornerMask(rect, radius));
}

void MainWindow::updateViewStruts()
{
    XWindowInterface::instance()->setViewStruts(this, m_settings->direction(), geometry());
}

void MainWindow::onAnimationValueChanged(const QVariant &value)
{
    QRect geometry = value.toRect();
    setGeometry(geometry);
    updateBlurRegion();
}

QRegion MainWindow::cornerMask(const QRect &rect, const int r)
{
    QRegion region;
    // middle and borders
    region += rect.adjusted(r, 0, -r, 0);
    region += rect.adjusted(0, r, 0, -r);

    // top left
    QRect corner(rect.topLeft(), QSize(r * 2, r * 2));
    region += QRegion(corner, QRegion::Ellipse);

    // top right
    corner.moveTopRight(rect.topRight());
    region += QRegion(corner, QRegion::Ellipse);

    // bottom left
    corner.moveBottomLeft(rect.bottomLeft());
    region += QRegion(corner, QRegion::Ellipse);

    // bottom right
    corner.moveBottomRight(rect.bottomRight());
    region += QRegion(corner, QRegion::Ellipse);

    return region;
}
