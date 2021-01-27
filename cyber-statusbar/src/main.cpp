#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQuickView>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication app(argc, argv);

    MainWindow w;

    return app.exec();
}
