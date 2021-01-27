#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "desktopview.h"
#include "settings.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    qmlRegisterType<Settings>("org.cyber.Desktop", 1, 0, "Settings");

    DesktopView view;
    view.show();

    return app.exec();
}
