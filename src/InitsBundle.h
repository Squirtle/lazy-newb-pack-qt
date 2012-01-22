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

    virtual QString author() const;
    virtual QString description() const;
    virtual QString dinitPath();
    virtual QPixmap icon() const;
    virtual QString initPath();
    virtual QString name() const;
    virtual QString packId() const;
    virtual QString prettyVersion() const;
    virtual int version() const;
    virtual GameDataTypes provides() const;

    virtual QObject* objectBase() { return this; }
    virtual const QObject* objectBase() const { return this; }

};

#endif // INITSBUNDLE_H
