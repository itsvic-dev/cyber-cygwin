#include "application.h"
#include "sessionadaptor.h"

#include <QDBusConnection>
#include <QStandardPaths>
#include <QSettings>
#include <QProcess>
#include <QDebug>
#include <QDir>

Application::Application(int &argc, char **argv)
    : QApplication(argc, argv)
    , m_processManager(new ProcessManager)
{
    new SessionAdaptor(this);

    // connect to D-Bus and register as an object:
    QDBusConnection::sessionBus().registerService(QStringLiteral("org.cyber.Session"));
    QDBusConnection::sessionBus().registerObject(QStringLiteral("/Session"), this);

    createConfigDirectory();
    initEnvironments();
    initLanguage();
    initScreenScaleFactors();

    if (!syncDBusEnvironment()) {
        // Startup error
        qDebug() << "Could not sync environment to dbus.";
    }

    QTimer::singleShot(100, m_processManager, &ProcessManager::start);
}

void Application::initEnvironments()
{
    // Set defaults
    if (qEnvironmentVariableIsEmpty("XDG_DATA_HOME"))
        qputenv("XDG_DATA_HOME", QDir::home().absoluteFilePath(QStringLiteral(".local/share")).toLocal8Bit());
    if (qEnvironmentVariableIsEmpty("XDG_DESKTOP_DIR"))
        qputenv("XDG_DESKTOP_DIR", QDir::home().absoluteFilePath(QStringLiteral("/Desktop")).toLocal8Bit());
    if (qEnvironmentVariableIsEmpty("XDG_CONFIG_HOME"))
        qputenv("XDG_CONFIG_HOME", QDir::home().absoluteFilePath(QStringLiteral(".config")).toLocal8Bit());
    if (qEnvironmentVariableIsEmpty("XDG_CACHE_HOME"))
        qputenv("XDG_CACHE_HOME", QDir::home().absoluteFilePath(QStringLiteral(".cache")).toLocal8Bit());
    if (qEnvironmentVariableIsEmpty("XDG_DATA_DIRS"))
        qputenv("XDG_DATA_DIRS", "/usr/local/share/:/usr/share/");
    if (qEnvironmentVariableIsEmpty("XDG_CONFIG_DIRS"))
        qputenv("XDG_CONFIG_DIRS", "/etc/xdg");

    // Environment
    qputenv("DESKTOP_SESSION", "Cyber");
    qputenv("XDG_CURRENT_DESKTOP", "Cyber");
    qputenv("XDG_SESSION_DESKTOP", "Cyber");

    qputenv("QT_QPA_PLATFORMTHEME", "cyber");
    qputenv("QT_PLATFORM_PLUGIN", "cyber");

    qputenv("QT_QUICK_CONTROLS_STYLE", "meui-style");
}

void Application::initLanguage()
{
    QSettings settings(QSettings::UserScope, "cyberos", "language");
    QString value = settings.value("language", "en_US").toString();
    QString str = QString("%1.UTF-8").arg(value);

    const auto lcValues = {
        "LANG", "LC_NUMERIC", "LC_TIME", "LC_MONETARY", "LC_MEASUREMENT", "LC_COLLATE", "LC_CTYPE"
    };

    for (auto lc : lcValues) {
        const QString value = str;
        if (!value.isEmpty()) {
            qputenv(lc, value.toUtf8());
        }
    }

    if (!value.isEmpty()) {
        qputenv("LANGUAGE", value.toUtf8());
    }
}

void Application::initScreenScaleFactors()
{
    QSettings settings(QSettings::UserScope, "cyberos", "theme");
    qreal scaleFactor = settings.value("PixelRatio", 1.0).toReal();

    qputenv("QT_SCREEN_SCALE_FACTORS", QByteArray::number(scaleFactor));

    if (std::floor(scaleFactor) > 1) {
        qputenv("GDK_SCALE", QByteArray::number(scaleFactor, 'g', 0));
        qputenv("GDK_DPI_SCALE", QByteArray::number(1.0 / scaleFactor, 'g', 3));
    }
}

bool Application::syncDBusEnvironment()
{
    int exitCode = 0;

    // At this point all environment variables are set, let's send it to the DBus session server to update the activation environment
    if (!QStandardPaths::findExecutable(QStringLiteral("dbus-update-activation-environment")).isEmpty()) {
        exitCode = runSync(QStringLiteral("dbus-update-activation-environment"), { QStringLiteral("--systemd"), QStringLiteral("--all") });
    }

    return exitCode == 0;
}

void Application::createConfigDirectory()
{
    const QString configDir = QStandardPaths::writableLocation(QStandardPaths::GenericConfigLocation);

    if (!QDir().mkpath(configDir))
        qDebug() << "Could not create config directory XDG_CONFIG_HOME: " << configDir;
}

int Application::runSync(const QString &program, const QStringList &args, const QStringList &env)
{
    QProcess p;

    if (!env.isEmpty())
        p.setEnvironment(QProcess::systemEnvironment() << env);

    p.setProcessChannelMode(QProcess::ForwardedChannels);
    p.start(program, args);
    p.waitForFinished(-1);

    if (p.exitCode()) {
        qWarning() << program << args << "exited with code" << p.exitCode();
    }

    return p.exitCode();
}
