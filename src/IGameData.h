#ifndef IGAMEDATA_H
#define IGAMEDATA_H

#include <QtilitiesCore/IObjectBase>

#include <QPixmap>

class IGameData : virtual public Qtilities::Core::Interfaces::IObjectBase
{
public:
    enum GameDataType {
       NoData = 0x0, //!< Contains Nothing
       Graphics = 0x1, //!< Contains graphics
       Tileset = 0x2, //!< Contains a tileset
       Inits = 0x4, //!< Contains init and d_init files
       Keybinds = 0x8, //!< Contains keybinds

    };
    Q_DECLARE_FLAGS(GameDataTypes, GameDataType)

    IGameData() {}
    virtual ~IGameData() {}

    /**
      * The name of this bundle This is the user visible name.
      * e.g., "Mayday's Graphics Pack"
      *       "Default Configuration"
      */
    virtual QString name() const = 0;

    /**
     * The type of data this bundle provides
     * e.g., return IGameData::Graphics | IGameData::Tileset
     */
    virtual GameDataTypes provides() const = 0;

    /**
      * A string that uniquely identifies this data bundle
      * E.g., "mayday"
      *       "defaults"
      */
    virtual QString packId() const = 0;

    /**
      * The version number for this bundle.
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
      * The author of this data bundle/
      * e.g., "Tarn Adams"
      *       "John Coltrane"
      */
    virtual QString author() const = 0;

    /**
      * A blurb, presumably about this data bundle
      * e.g., "This is my super graphics pack"
      *       "Default configuration files for DF v31.25"
      */
    virtual QString description() const = 0;

    /**
      * A pretty icon for the bundle.
      * Optional. Return QPixmap() if there is none.
      */
    virtual QPixmap icon() const = 0;

};
Q_DECLARE_OPERATORS_FOR_FLAGS(IGameData::GameDataTypes)
#endif // IGAMEDATA_H
