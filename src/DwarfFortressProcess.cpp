#include "DwarfFortressProcess.h"

#ifdef Q_WS_X11
#include <sys/types.h>
#include <sys/stat.h>
#endif

DwarfFortressProcess::DwarfFortressProcess(QObject *parent) :
    QProcess(parent)
{}

void DwarfFortressProcess::setupChildProcess()
{
#ifdef Q_WS_X11
    ::umask(0002);
#endif
}
