#include "LocalKeybindsBundle.h"

#include "LocalKeybindsProvider.h"

LocalKeybindsBundle::LocalKeybindsBundle( const QString& path, QObject* parent ): QObject( parent ), m_path(path)
{
    parseManifest(path, true);
}

LocalKeybindsBundle::~LocalKeybindsBundle()
{
}

QString LocalKeybindsBundle::keybindsFilePath()
{
    if( LocalKeybindsProvider::verifyKeybinds(m_path) )
        return m_path;
    return QString();
}

bool LocalKeybindsBundle::dataAvailable() const
{
    return LocalKeybindsProvider::verifyKeybinds(m_path);
}

IGameData::GameDataTypes LocalKeybindsBundle::provides() const
{
    return IGameData::Keybinds;
}
