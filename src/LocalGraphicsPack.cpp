#include "LocalGraphicsPack.h"

#include "LocalGraphicsProvider.h"

#include <yaml-cpp/yaml.h>
#include <fstream>
#include <functional>

#include <QFileInfo>
#include <QDir>

LocalGraphicsPack::LocalGraphicsPack(const QString &path, QObject *parent)
    : QObject(parent)
    , m_path( path )
{
    parseIndex();
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

QPixmap LocalGraphicsPack::icon() const
{
    return QPixmap( m_iconPath );
}

QString LocalGraphicsPack::description() const
{
    return m_description;
}

QString LocalGraphicsPack::author() const
{
    return m_author;
}

QString LocalGraphicsPack::prettyVersion() const
{
    return m_prettyVersion;
}

int LocalGraphicsPack::version() const
{
    return m_version;
}

QString LocalGraphicsPack::packId() const
{
    return m_name;
}

IGameData::GameDataTypes LocalGraphicsPack::provides() const
{
    return IGameData::Graphics | IGameData::Tileset;
}

QString LocalGraphicsPack::name() const
{
    return m_name;
}

void LocalGraphicsPack::parseIndex()
{
    QFileInfo yaml_info(m_path + QDir::separator() + "index.yml");
    if( !yaml_info.exists() ) return;
    std::ifstream fin(yaml_info.absoluteFilePath().toStdString());
    YAML::Parser parser(fin);
    YAML::Node doc;
    parser.GetNextDocument(doc);
    const YAML::Node &doc_cap = doc;

    std::function<QString(std::string)> getValue = [&doc_cap](std::string key) {
        std::string value;
        doc_cap[key] >> value;
        return QString::fromStdString(value);
    };

    m_name = getValue("name");
    m_author = getValue("author");
    m_description = getValue("description");
    m_prettyVersion = getValue("prettyVersion");
    doc["version"] >> m_version;

    const QString icon_path = m_path + QDir::separator() + "icon.png";
    if( QFileInfo(icon_path).exists() )
        m_iconPath = icon_path;
}
