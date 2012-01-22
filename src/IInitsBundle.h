#ifndef IINITSBUNDLE_H
#define IINITSBUNDLE_H

#include "IGameData.h"
#include <QPixmap>
#include <QString>

class IInitsBundle : public virtual IGameData
{

public:
    IInitsBundle() {}
    virtual ~IInitsBundle() {}

    /**
     * Path to the init.txt file
     */
    virtual QString initPath() = 0;

    /**
     * Path to the d_init.txt file
     */
    virtual QString dinitPath() = 0;

};

Q_DECLARE_INTERFACE(IInitsBundle, "com.lazynewb.IInitsBundle/1.0");
#endif // IINITSBUNDLE_H
