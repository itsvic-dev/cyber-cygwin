#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QQuickView>
#include <QVariantAnimation>
#include <QTimer>

#include "battery.h"
#include "volumemanager.h"
#include "volumecontrolwindow.h"
#include "statusnotifier/statusnotifiermodel.h"

class MainWindow : public QQuickView
{
    Q_OBJECT

public:
    explicit MainWindow(QQuickView *parent = nullptr);

    void resizeWindow();
    void updateViewStruts();

private:
    Battery *m_battery;
    VolumeManager *m_volumeManager;
    VolumeControlWindow *m_volumeControlWindow;
    StatusNotifierModel *m_statusNotifierModel;
};

#endif // MAINWINDOW_H
