#include "InitsBundle.h"

#include "LocalInitsProvider.h"

#include <QDir>

InitsBundle::InitsBundle( const QString& path, QObject* parent )
    : QObject(parent)
    , m_path( path )
{

    parseManifest(path);
}

InitsBundle::~InitsBundle()
{

}

QString InitsBundle::dinitPath()
{
    if( LocalInitsProvider::verifyInitsPack(m_path) )
        return m_path + QDir::separator() + "d_init.txt";
    return QString();
}

QString InitsBundle::initPath()
{
    if( LocalInitsProvider::verifyInitsPack(m_path) )
        return m_path + QDir::separator() + "init.txt";
    return QString();
}

IGameData::GameDataTypes InitsBundle::provides() const
{
    // In case the there isn't a yaml manifest
    if( LocalGameData::provides() == IGameData::NoData && LocalInitsProvider::verifyInitsPack(m_path) )
        return IGameData::Inits;
    return LocalGameData::provides();
}

bool InitsBundle::dataAvailable() const
{
    return LocalInitsProvider::verifyInitsPack(m_path);
}

