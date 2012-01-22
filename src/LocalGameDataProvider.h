#ifndef LOCALGAMEDATAPROVIDER_H
#define LOCALGAMEDATAPROVIDER_H

#include "IGameDataProvider.h"

#include <QObject>
#include <QString>

class LocalGraphicsProvider;

class LocalGameDataProvider : public QObject, public IGameDataProvider
{
    Q_OBJECT
    Q_INTERFACES(IGameDataProvider)
public:
    LocalGameDataProvider(const QString & path, QObject *parent = nullptr);
    virtual ~LocalGameDataProvider(){}

    virtual QObject* objectBase() { return this; }
    virtual const QObject* objectBase() const { return this; }

    virtual IGraphicsProvider* graphicsProvider() const;

private:
    QString m_path;
    LocalGraphicsProvider* m_graphicsProvider;
};

#endif // LOCALGAMEDATAPROVIDER_H
