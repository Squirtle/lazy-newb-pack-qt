#ifndef IINITSPROVIDER_H
#define IINITSPROVIDER_H

#include <QtilitiesCore/IObjectBase>

#include "IGraphicsProvider.h"

/**
  * Provides access init files.
  */
class IInitsProvider : virtual public Qtilities::Core::Interfaces::IObjectBase
{
public:
    IInitsProvider() {}
    virtual ~IInitsProvider() {}

    /**
     * Path to the init.txt file
     */
    virtual QString initPath() = 0;

    /**
     * Path to the d_init.txt file
     */
    virtual QString dinitPath() = 0;

};

Q_DECLARE_INTERFACE(IInitsProvider, "com.lazynewb.IInitsProvider/1.0");
#endif // IINITSPROVIDER_H
