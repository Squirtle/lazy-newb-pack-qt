#include "LocalGameDataProvider.h"

#include "LocalGraphicsProvider.h"

#include <QDir>
#include <QDebug>

LocalGameDataProvider::LocalGameDataProvider(const QString & path, QObject *parent)
    : QObject(parent)
    , m_path(path)
    , m_graphicsProvider(nullptr)
{
    QDir dir(m_path);
    if(!dir.exists()) { qWarning() << "LocalGameDataProvider:: path doesn't exist" << path; /* TODO: handle */ }

    m_graphicsProvider =  new LocalGraphicsProvider(path + QDir::separator() + "Graphics", this);

}

IGraphicsProvider* LocalGameDataProvider::graphicsProvider() const
{
    return m_graphicsProvider;
}

