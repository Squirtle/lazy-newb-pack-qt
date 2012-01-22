#ifndef IGAMEDATAPROVIDER_H
#define IGAMEDATAPROVIDER_H

#include <QtilitiesCore/IObjectBase>

#include "IGraphicsProvider.h"

/**
  * Provides access to all types of game data
  */
class IGameDataProvider : virtual public Qtilities::Core::Interfaces::IObjectBase
{
public:
    IGameDataProvider() {}
    virtual ~IGameDataProvider() {}

    virtual IGraphicsProvider* graphicsProvider() const = 0;

};

Q_DECLARE_INTERFACE(IGameDataProvider, "com.lazynewb.IGameDataProvider/1.0");

#endif // IGAMEDATAPROVIDER_H
