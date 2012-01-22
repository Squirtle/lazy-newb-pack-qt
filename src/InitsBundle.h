#ifndef INITSBUNDLE_H
#define INITSBUNDLE_H

#include "IInitsBundle.h"

class InitsBundle : public IInitsBundle
{
Q_OBJECT
Q_INTERFACES(IInitsBundle);
public:
    InitsBundle();
    virtual ~InitsBundle();

    virtual GameDataTypes provides() const;

    virtual QObject* objectBase() { return this; }
    virtual const QObject* objectBase() const { return this; }

};

#endif // INITSBUNDLE_H
