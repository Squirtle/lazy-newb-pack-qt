#ifndef IGRAPHICSPACK_H
#define IGRAPHICSPACK_H

#include <QtilitiesCore/IObjectBase>

#include <QPixmap>

class IGraphicsPack : virtual public Qtilities::Core::Interfaces::IObjectBase
{
public:
    IGraphicsPack() {}
    virtual ~IGraphicsPack() {}

    /**
      * The name of the graphics pack. This is the user visible name.
      * e.g., "Mayday's Graphics Pack"
      */
    virtual QString name() const = 0;

    /**
      * A string that uniquely identifies this pack.
      * E.g., "mayday"
      */
    virtual QString packId() const = 0;

    /**
      * The version number of the graphics pack.
      * This value will be used for version comparisons.
      * e.g., "15"
      */
    virtual int version() const = 0;

    /**
      * The version number in a human readable form.
      * e.g., "v1.5"
      */
    virtual QString prettyVersion() const = 0;

    /**
      * The author of this graphics pack.
      * e.g., "John Coltrane"
      */
    virtual QString author() const = 0;

    /**
      * A blurb, presumably about the graphics pack.
      * e.g., "This is my super graphics pack"
      */
    virtual QString description() const = 0;

    /**
      * A pretty icon for the pack
      */
    virtual QPixmap icon() const = 0;

    /**
      * Is the data available to install right now?
      */
    virtual bool dataAvailable() const = 0;

    /**
      * The path where we can get the pack's data.
      * This must be a dir containing the 'data' and 'raw' subdirs
      */
    virtual QString dataPath() const = 0;

};

Q_DECLARE_INTERFACE(IGraphicsPack, "com.lazynewb.IGraphicsPack/1.0");
#endif // IGRAPHICSPACK_H
