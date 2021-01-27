#ifndef STATUSNOTIFIERITEMINTERFACE_H
#define STATUSNOTIFIERITEMINTERFACE_H

#include <QObject>
#include <QByteArray>
#include <QList>
#include <QMap>
#include <QString>
#include <QStringList>
#include <QVariant>
#include <QtDBus>
#include "dbustypes.h"

/*
 * Proxy class for interface org.kde.StatusNotifierItem
 */
class StatusNotifierItemInterface: public QDBusAbstractInterface
{
    Q_OBJECT
public:
    static inline const char *staticInterfaceName()
    { return "org.kde.StatusNotifierItem"; }

public:
    StatusNotifierItemInterface(const QString &service, const QString &path, const QDBusConnection &connection, QObject *parent = nullptr);

    ~StatusNotifierItemInterface();

    Q_PROPERTY(QString AttentionIconName READ attentionIconName)
    inline QString attentionIconName() const
    { return qvariant_cast< QString >(property("AttentionIconName")); }

    Q_PROPERTY(IconPixmapList AttentionIconPixmap READ attentionIconPixmap)
    inline IconPixmapList attentionIconPixmap() const
    { return qvariant_cast< IconPixmapList >(property("AttentionIconPixmap")); }

    Q_PROPERTY(QString AttentionMovieName READ attentionMovieName)
    inline QString attentionMovieName() const
    { return qvariant_cast< QString >(property("AttentionMovieName")); }

    Q_PROPERTY(QString Category READ category)
    inline QString category() const
    { return qvariant_cast< QString >(property("Category")); }

    Q_PROPERTY(QString IconName READ iconName)
    inline QString iconName() const
    { return qvariant_cast< QString >(property("IconName")); }

    Q_PROPERTY(IconPixmapList IconPixmap READ iconPixmap)
    inline IconPixmapList iconPixmap() const
    { return qvariant_cast< IconPixmapList >(property("IconPixmap")); }

    Q_PROPERTY(QString IconThemePath READ iconThemePath)
    inline QString iconThemePath() const
    { return qvariant_cast< QString >(property("IconThemePath")); }

    Q_PROPERTY(QString Id READ id)
    inline QString id() const
    { return qvariant_cast< QString >(property("Id")); }

    Q_PROPERTY(bool ItemIsMenu READ itemIsMenu)
    inline bool itemIsMenu() const
    { return qvariant_cast< bool >(property("ItemIsMenu")); }

    Q_PROPERTY(QDBusObjectPath Menu READ menu)
    inline QDBusObjectPath menu() const
    { return qvariant_cast< QDBusObjectPath >(property("Menu")); }

    Q_PROPERTY(QString OverlayIconName READ overlayIconName)
    inline QString overlayIconName() const
    { return qvariant_cast< QString >(property("OverlayIconName")); }

    Q_PROPERTY(IconPixmapList OverlayIconPixmap READ overlayIconPixmap)
    inline IconPixmapList overlayIconPixmap() const
    { return qvariant_cast< IconPixmapList >(property("OverlayIconPixmap")); }

    Q_PROPERTY(QString Status READ status)
    inline QString status() const
    { return qvariant_cast< QString >(property("Status")); }

    Q_PROPERTY(QString Title READ title)
    inline QString title() const
    { return qvariant_cast< QString >(property("Title")); }

    Q_PROPERTY(ToolTip ToolTip READ toolTip)
    inline ToolTip toolTip() const
    { return qvariant_cast< ToolTip >(property("ToolTip")); }

    Q_PROPERTY(int WindowId READ windowId)
    inline int windowId() const
    { return qvariant_cast< int >(property("WindowId")); }

public Q_SLOTS: // METHODS
    inline QDBusPendingReply<> Activate(int x, int y)
    {
        QList<QVariant> argumentList;
        argumentList << QVariant::fromValue(x) << QVariant::fromValue(y);
        return asyncCallWithArgumentList(QLatin1String("Activate"), argumentList);
    }

    inline QDBusPendingReply<> ContextMenu(int x, int y)
    {
        QList<QVariant> argumentList;
        argumentList << QVariant::fromValue(x) << QVariant::fromValue(y);
        return asyncCallWithArgumentList(QLatin1String("ContextMenu"), argumentList);
    }

    inline QDBusPendingReply<> Scroll(int delta, const QString &orientation)
    {
        QList<QVariant> argumentList;
        argumentList << QVariant::fromValue(delta) << QVariant::fromValue(orientation);
        return asyncCallWithArgumentList(QLatin1String("Scroll"), argumentList);
    }

    inline QDBusPendingReply<> SecondaryActivate(int x, int y)
    {
        QList<QVariant> argumentList;
        argumentList << QVariant::fromValue(x) << QVariant::fromValue(y);
        return asyncCallWithArgumentList(QLatin1String("SecondaryActivate"), argumentList);
    }

Q_SIGNALS: // SIGNALS
    void NewAttentionIcon();
    void NewIcon();
    void NewOverlayIcon();
    void NewStatus(const QString &status);
    void NewTitle();
    void NewToolTip();
};

namespace org {
  namespace kde {
    typedef ::StatusNotifierItemInterface StatusNotifierItem;
  }
}
#endif
