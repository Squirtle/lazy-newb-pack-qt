#include "LocalGameDataProvider.h"

#include "LocalGraphicsProvider.h"
#include "LocalInitsProvider.h"

#include <QDir>
#include <QDebug>

LocalGameDataProvider::LocalGameDataProvider(const QDir & base, QObject *parent)
    : QObject(parent)
    , m_path(base)
    , m_graphicsProvider(nullptr)
{
    QDir dir(m_path);
    if(!dir.exists()) { qWarning() << "LocalGameDataProvider:: path doesn't exist" << base.path(); /* TODO: handle */ }

    m_graphicsProvider =  new LocalGraphicsProvider(base.path()+ QDir::separator() + "Graphics", this);
    m_initsProvider = new LocalInitsProvider(base.path() + QDir::separator() + "Defaults", this);

}

IGraphicsProvider* LocalGameDataProvider::graphicsProvider() const
{
    return m_graphicsProvider;
}

IInitsProvider* LocalGameDataProvider::initsProvider() const
{
    return m_initsProvider;
}
