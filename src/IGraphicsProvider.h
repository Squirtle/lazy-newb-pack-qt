#ifndef IGRAPHICSPROVIDER_H
#define IGRAPHICSPROVIDER_H

#include <QtilitiesCore/IObjectBase>

/**
  * Provides access to graphics packs;
  */
class IGraphicsProvider : virtual public Qtilities::Core::Interfaces::IObjectBase
{
public  :
    IGraphicsProvider() {}
    virtual ~IGraphicsProvider() {}

};

Q_DECLARE_INTERFACE(IGraphicsProvider, "com.lazynewb.IGraphicsProvider/1.0");
#endif // IGRAPHICSPROVIDER_H
