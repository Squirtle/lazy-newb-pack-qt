#ifndef DWARFORTRESSPROCESS_H
#define DWARFORTRESSPROCESS_H

#include <QProcess>

class DwarfFortressProcess : public QProcess
{
    Q_OBJECT
public:
    explicit DwarfFortressProcess(QObject *parent = nullptr);
    
protected:
    void setupChildProcess();
};

#endif // DWARFORTRESSPROCESS_H
