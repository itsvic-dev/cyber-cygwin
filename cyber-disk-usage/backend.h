#ifndef BACKEND_H
#define BACKEND_H

#include <QObject>
#include <QString>
#include <QStorageInfo>
#include <QVariant>
#include <QDebug>
#include <QMap>
#include <QtMath>

class Drive : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString name READ name NOTIFY stub)
    Q_PROPERTY(QString usage READ usage NOTIFY stub)

public:
    explicit Drive(QObject *parent = nullptr);

    QString name();
    QString usage();

    // Only for use by Backend::getDrives()
    void setStorageInfoDrive(QStorageInfo drive);

signals:
    void stub();

private:
    QStorageInfo m_drive;
};

class Backend : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QVariantList getDrives READ getDrives NOTIFY stub)

public:
    explicit Backend(QObject *parent = nullptr);

    QVariantList getDrives();

signals:
    void stub();
};

#endif
