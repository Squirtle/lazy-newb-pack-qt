#ifndef INITSBUNDLE_H
#define INITSBUNDLE_H

#include "IInitsBundle.h"
#include "LocalGameData.h"

#include <QObject>

class InitsBundle : public QObject, public IInitsBundle, public LocalGameData
{
Q_OBJECT
Q_INTERFACES(IInitsBundle);
public:
    InitsBundle(const QString &path, QObject *parent = nullptr);
    virtual ~InitsBundle();

    virtual GameDataTypes provides() const;

    virtual QObject* objectBase() { return this; }
    virtual const QObject* objectBase() const { return this; }

    virtual QString initPath();
    virtual QString dinitPath();

private:
    QString m_path;
};

#endif // INITSBUNDLE_H
