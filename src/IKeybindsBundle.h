#ifndef IKEYBINDSBUNDLE_H
#define IKEYBINDSBUNDLE_H

#include "IGameData.h"

class IKeybindsBundle : public virtual IGameData
{

public:
    IKeybindsBundle() {}
    virtual ~IKeybindsBundle() {}
    /**
     * Full path to the keybinds file.
     */
    virtual QString keybindsFilePath() = 0;

};
Q_DECLARE_INTERFACE(IKeybindsBundle, "com.lazynewb.IKeybindsBundle/1.0");

#endif // IKEYBINDSBUNDLE_H
