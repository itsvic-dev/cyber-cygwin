#include "windowcontrol.h"
#include <QX11Info>

#include <KF5/KWindowSystem/KWindowSystem>
#include <KF5/KWindowSystem/NETWM>

WindowControl::WindowControl(QObject *parent)
    : QObject(parent)
    , m_isMaximized(false)
{
    // Init
    onWindowChanged();

    connect(KWindowSystem::self(), &KWindowSystem::activeWindowChanged, this, &WindowControl::onWindowChanged);
    connect(KWindowSystem::self(), static_cast<void (KWindowSystem::*)(WId)>(&KWindowSystem::windowChanged),
            this, &WindowControl::onWindowChanged);
}

QString WindowControl::title() const
{
    return m_title;
}

bool WindowControl::isMaximized() const
{
    return m_isMaximized;
}

void WindowControl::minimize()
{
    KWindowSystem::minimizeWindow(KWindowSystem::activeWindow());
}

void WindowControl::restore()
{
    KWindowSystem::clearState(KWindowSystem::activeWindow(), NET::Max);
}

void WindowControl::maximize()
{
    KWindowSystem::setState(KWindowSystem::activeWindow(), NET::Max);
}

void WindowControl::toggleMaximize()
{
    KWindowInfo info(KWindowSystem::activeWindow(), NET::WMState);
    bool isWindow = !info.hasState(NET::SkipTaskbar) ||
                     info.windowType(NET::UtilityMask) != NET::Utility ||
                     info.windowType(NET::DesktopMask) != NET::Desktop;

    if (!isWindow)
        return;

    m_isMaximized ? restore() : maximize();
}

void WindowControl::close()
{
    NETRootInfo(QX11Info::connection(), NET::CloseWindow).closeWindowRequest(KWindowSystem::activeWindow());
}

void WindowControl::onWindowChanged()
{
    KWindowInfo info(KWindowSystem::activeWindow(), NET::WMState | NET::WMVisibleName);

    QString title = info.visibleName();
    if (title != m_title) {
        m_title = title;
        emit titleChanged();
    }

    bool isMaximized = info.hasState(NET::Max);
    if (isMaximized != m_isMaximized) {
        m_isMaximized = isMaximized;
        emit maximizeChanged();
    }
}
