#ifndef DFDATAMANAGER_H
#define DFDATAMANAGER_H

#include <QObject>
#include <QPointer>

class IInitsBundle;
class DFDataManager;

typedef QPointer<DFDataManager> DFManagerPtr;

class DFDataManager : public QObject
{
Q_OBJECT
public:
    explicit DFDataManager( QObject* parent = nullptr );
    virtual ~DFDataManager();

    bool installInits(IInitsBundle* bundle);
};

#endif // DFDATAMANAGER_H
