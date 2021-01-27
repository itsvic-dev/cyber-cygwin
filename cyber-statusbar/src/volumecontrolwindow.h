#ifndef VOLUMECONTROLWINDOW_H
#define VOLUMECONTROLWINDOW_H

#include <QQuickView>
#include "volumemanager.h"

class VolumeControlWindow : public QQuickView
{
    Q_OBJECT

public:
    explicit VolumeControlWindow(QQuickView *parent = nullptr);

    Q_INVOKABLE void popup(const QPointF point);
    Q_INVOKABLE void hide();

protected:
    void showEvent(QShowEvent *) override;

private slots:
    void onActiveChanged();

private:
    VolumeManager *m_volumeManager;
};

#endif // VOLUMECONTROLWINDOW_H
