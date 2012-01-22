#ifndef LOCALGAMEDATAPROVIDER_H
#define LOCALGAMEDATAPROVIDER_H

#include "IGameDataProvider.h"

#include <QObject>
#include <QString>
#include <QDir>

class LocalGraphicsProvider;
class LocalInitsProvider;

/**
 * Locates and registers DataProviders for data in the old LNP data directory format
 * example:
 * path/
 * - Graphics
 * - - Mayday Graphics
 * - Defaults
 * - - data/
 * - Keybinds
 * - - keybind.txt
 * - - better_keybind.txt
 * etc
 */
class LocalGameDataProvider : public QObject, public IGameDataProvider
{
    Q_OBJECT
    Q_INTERFACES(IGameDataProvider)
public:
    LocalGameDataProvider(const QDir& base, QObject *parent = nullptr);
    virtual ~LocalGameDataProvider(){}

    virtual QObject* objectBase() { return this; }
    virtual const QObject* objectBase() const { return this; }

    virtual IGraphicsProvider* graphicsProvider() const;
    virtual IInitsProvider* initsProvider() const;

private:
    QDir m_path;
    LocalGraphicsProvider* m_graphicsProvider;
    LocalInitsProvider* m_initsProvider;
};

#endif // LOCALGAMEDATAPROVIDER_H
