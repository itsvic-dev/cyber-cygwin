#include "battery.h"
#include <QDateTime>
#include <QDBusArgument>
#include <QDBusReply>
#include <QDebug>

static const QString s_sServer = "org.cyber.Settings";
static const QString s_sPath = "/PrimaryBattery";
static const QString s_sInterface = "org.cyber.PrimaryBattery";

//DBus Battery Info Structure
struct BatteryInfo {
    uint time, state;
    double value;
};
Q_DECLARE_METATYPE(BatteryInfo)

const QDBusArgument &operator<<(QDBusArgument &argument, const BatteryInfo &info) {
    argument.beginStructure();
    argument << info.time << info.value << info.state;
    argument.endStructure();
    return argument;
}

const QDBusArgument &operator>>(const QDBusArgument &argument, BatteryInfo &info) {
    argument.beginStructure();
    argument >> info.time >> info.value >> info.state;
    argument.endStructure();
    return argument;
}

Battery::Battery(QObject *parent)
    : QObject(parent)
    , m_upowerInterface("org.freedesktop.UPower",
                        "/org/freedesktop/UPower",
                        "org.freedesktop.UPower",
                        QDBusConnection::systemBus())
    , m_interface("org.cyber.Settings",
                  "/PrimaryBattery",
                  "org.cyber.PrimaryBattery",
                  QDBusConnection::sessionBus())
    , m_available(false)
    , m_onBattery(false)
{
    m_available = m_interface.isValid() && !m_interface.lastError().isValid();

    if (m_available) {
        QDBusConnection::sessionBus().connect(s_sServer, s_sPath, s_sInterface, "chargeStateChanged", this, SLOT(chargeStateChanged(int)));
        QDBusConnection::sessionBus().connect(s_sServer, s_sPath, s_sInterface, "chargePercentChanged", this, SLOT(chargePercentChanged(int)));
        QDBusConnection::sessionBus().connect(s_sServer, s_sPath, s_sInterface, "lastChargedPercentChanged", this, SLOT(lastChargedPercentChanged()));
        QDBusConnection::sessionBus().connect(s_sServer, s_sPath, s_sInterface, "capacityChanged", this, SLOT(capacityChanged(int)));
        QDBusConnection::sessionBus().connect(s_sServer, s_sPath, s_sInterface, "remainingTimeChanged", this, SLOT(remainingTimeChanged(qlonglong)));

        QDBusInterface interface("org.freedesktop.UPower", "/org/freedesktop/UPower",
                                 "org.freedesktop.UPower", QDBusConnection::systemBus());

        QDBusConnection::systemBus().connect("org.freedesktop.UPower", "/org/freedesktop/UPower",
                                             "org.freedesktop.DBus.Properties",
                                             "PropertiesChanged", this,
                                             SLOT(onPropertiesChanged(QString, QVariantMap, QStringList)));

        if (interface.isValid()) {
            m_onBattery = interface.property("OnBattery").toBool();
        }

        m_udi = m_interface.property("udi").toString();

        emit validChanged();
    }
}

bool Battery::available() const
{
    return m_available;
}

bool Battery::onBattery() const
{
    return m_onBattery;
}

void Battery::refresh()
{
    m_interface.call("refresh");
}

QVariantList Battery::getHistory(const int timespan, const int resolution)
{
    QVariantList listValues;
    QVariantMap listItem;

    QDBusMessage historyMessage = QDBusMessage::createMethodCall("org.freedesktop.UPower", m_udi,
                                                                 "org.freedesktop.UPower.Device", "GetHistory");
    QVariantList historyMessageArguments;
    historyMessageArguments.append("charge");
    historyMessageArguments.append((uint) timespan);
    historyMessageArguments.append((uint) resolution);
    historyMessage.setArguments(historyMessageArguments);

    quint64 offset = QDateTime::currentDateTime().toSecsSinceEpoch();

    QDBusReply<QDBusArgument> historyArgument = QDBusConnection::systemBus().call(historyMessage);
    if (historyArgument.isValid()) {
        QDBusArgument arrayArgument = historyArgument.value();
        arrayArgument.beginArray();
        while (!arrayArgument.atEnd()) {
            BatteryInfo info;
            arrayArgument >> info;
            listItem.insert("time", offset - info.time);
            listItem.insert("value", info.value);
            listValues += listItem;
        }
    }

    return listValues;
}

int Battery::chargeState() const
{
    return m_interface.property("chargeState").toInt();
}

int Battery::chargePercent() const
{
    return m_interface.property("chargePercent").toInt();
}

int Battery::lastChargedPercent() const
{
    return m_interface.property("lastChargedPercent").toInt();
}

int Battery::capacity() const
{
    return m_interface.property("capacity").toInt();
}

QString Battery::statusString() const
{
    return m_interface.property("statusString").toString();
}

QString Battery::lastChargedTime() const
{
    return m_interface.property("lastChargedTime").toString();
}

void Battery::onPropertiesChanged(const QString &ifaceName, const QVariantMap &changedProps, const QStringList &invalidatedProps)
{
    Q_UNUSED(ifaceName);
    Q_UNUSED(changedProps);
    Q_UNUSED(invalidatedProps);

    bool onBattery = m_upowerInterface.property("OnBattery").toBool();
    if (onBattery != m_onBattery) {
        m_onBattery = onBattery;
        m_interface.call("refresh");
        emit onBatteryChanged();
    }
}
