#include "LocalGraphicsPack.h"

#include "LocalGraphicsProvider.h"

#include <QDir>

LocalGraphicsPack::LocalGraphicsPack(const QString &path, QObject *parent)
    : QObject(parent)
    , m_path( path )
{
    const QString manifest( m_path + QDir::separator() + "index.yml" );
    parseManifest( manifest );
}

LocalGraphicsPack::~LocalGraphicsPack()
{
}

QString LocalGraphicsPack::dataPath() const
{
    return m_path;
}

bool LocalGraphicsPack::dataAvailable() const
{
    return LocalGraphicsProvider::verifyGraphicsPack(m_path);
}
