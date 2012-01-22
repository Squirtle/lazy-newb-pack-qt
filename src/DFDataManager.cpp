#include "DFDataManager.h"

#include "IInitsBundle.h"
#include "DwarfFortress.h"

#include <QFile>

DFDataManager::DFDataManager( QObject* parent ) : QObject(parent)
{

}

DFDataManager::~DFDataManager()
{

}

bool DFDataManager::installInits( IInitsBundle* bundle )
{
    QFile oldinit(DwarfFortress::instance().getInitPath()), newinit(bundle->initPath());
    QFile olddinit(DwarfFortress::instance().getDInitPath()), newdinit(bundle->dinitPath());

    Q_ASSERT(newinit.exists());
    Q_ASSERT(newdinit.exists());
    if( !newdinit.exists() || !newinit.exists() ) return false;

    oldinit.remove();
    olddinit.remove();
    newinit.copy(DwarfFortress::instance().getInitPath());
    newdinit.copy(DwarfFortress::instance().getDInitPath());

    DwarfFortress::instance().notifyChange();
    return true;
}
