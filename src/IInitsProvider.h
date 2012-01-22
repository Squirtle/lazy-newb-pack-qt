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

};

Q_DECLARE_INTERFACE(IInitsProvider, "com.lazynewb.IInitsProvider/1.0");
#endif // IINITSPROVIDER_H
