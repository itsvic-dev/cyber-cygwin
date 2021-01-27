#include "backend.h"

Drive::Drive(QObject *parent) :
    QObject(parent)
{
}

QString Drive::name()
{
    QString displayName = m_drive.displayName();
    if (displayName != m_drive.rootPath())
        return displayName + " (" + m_drive.rootPath() + ")";
    return displayName;
}

QString Drive::usage()
{
    float bytesUsed = m_drive.bytesTotal() - m_drive.bytesFree();
    if (m_drive.bytesTotal() / 1024 / 1024 / 1024 == 0) // is less than 1GB?
    {
        // return in MB instead
        float mbUsed = bytesUsed / 1024 / 1024;
        float mbTotal = float(m_drive.bytesTotal()) / 1024 / 1024;
        return QString::number(qCeil(mbUsed)) + "/" + QString::number(qCeil(mbTotal)) + tr(" MB used");
    }
    float gbUsed = bytesUsed / 1024 / 1024 / 1024;
    float gbTotal = float(m_drive.bytesTotal()) / 1024 / 1024 / 1024;
    return QString::number(qCeil(gbUsed)) + "/" + QString::number(qCeil(gbTotal)) + tr(" GB used");
}

void Drive::setStorageInfoDrive(QStorageInfo storageInfo) {
    m_drive = storageInfo;
}


Backend::Backend(QObject *parent) :
    QObject(parent)
{
}

QVariantList Backend::getDrives()
{
    QVariantList list;
    foreach (const QStorageInfo &storage, QStorageInfo::mountedVolumes())
    {
        if (storage.isValid() && storage.isReady())
            if (!storage.isReadOnly() && storage.bytesTotal())
            {
                // System partitions, we don't care about those.
                if (storage.rootPath().startsWith("/tmp") ||
                    storage.rootPath().startsWith("/run"))
                    continue;
                Drive drive;
                drive.setStorageInfoDrive(storage);
                QVariantMap internalMap;
                internalMap.insert(QString("name"), QVariant(drive.name()));
                internalMap.insert(QString("usage"), QVariant(drive.usage()));
                list.append(internalMap);
            }
    }
    return list;
}
