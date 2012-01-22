#include "LocalGraphicsPack.h"

#include "LocalGraphicsProvider.h"

#include <QDir>

LocalGraphicsPack::LocalGraphicsPack(const QString &path, QObject *parent)
    : QObject(parent)
    , m_path( path )
{
    parseManifest( path );
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

IGameData::GameDataTypes LocalGraphicsPack::provides() const
{
    // In case the there isn't a yaml manifest
    if( LocalGameData::provides() == IGameData::NoData )
        return IGameData::Graphics | IGameData::Tileset;
    return LocalGameData::provides();
}
