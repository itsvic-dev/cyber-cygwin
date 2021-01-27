#ifndef FONTS_H
#define FONTS_H

#include <QObject>
#include <QDBusConnection>
#include <QDBusInterface>

class Fonts : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString fixedFont READ fixedFont NOTIFY stub)

public:
    explicit Fonts(QObject *parent = nullptr);

    QString fixedFont();

signals:
    void stub();
};

#endif // FONTS_H
