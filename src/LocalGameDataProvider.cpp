#include "LocalGameDataProvider.h"

#include "LocalGraphicsProvider.h"

#include <QDir>

LocalGameDataProvider::LocalGameDataProvider(const QString & path, QObject *parent)
    : QObject(parent)
    , m_path(path)
    , m_graphicsProvider(nullptr)
{
    QDir dir(m_path);
    if(!dir.exists()) { /* TODO */ }

    m_graphicsProvider =  new LocalGraphicsProvider(path + QDir::separator() + "Graphics", this);

}
