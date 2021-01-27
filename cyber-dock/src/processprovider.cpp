#include "processprovider.h"
#include <QProcess>
#include <QDir>

ProcessProvider::ProcessProvider(QObject *parent)
    : QObject(parent)
{

}

bool ProcessProvider::start(const QString &exec, QStringList args)
{
    /* // More fucking Qt 5.10 code which I have to deal with.
    QProcess process;
    process.setProgram(exec);
    process.setArguments(args);
    return process.startDetached();
    */
    return QProcess::startDetached(exec, args, QDir::currentPath());
}
