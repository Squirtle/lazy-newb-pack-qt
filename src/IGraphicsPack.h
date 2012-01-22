#ifndef IGRAPHICSPACK_H
#define IGRAPHICSPACK_H

#include "IGameData.h"
#include <QPixmap>

class IGraphicsPack : virtual public IGameData
{
public:
    IGraphicsPack() {}
    virtual ~IGraphicsPack() {}

    /**
      * Is the data available to install right now?
      * Example, if it wasn't available, perhaps we need to download it.
      */
    virtual bool dataAvailable() const = 0;

    /**
      * The path where we can get the data bundle.
      * A dir or archive file.
      * This must be a dir containing the 'data' and 'raw' subdirs
      */
    virtual QString dataPath() const = 0;

};

Q_DECLARE_INTERFACE(IGraphicsPack, "com.lazynewb.IGraphicsPack/1.0");
#endif // IGRAPHICSPACK_H
