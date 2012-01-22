#include "LocalGameData.h"

#include <yaml-cpp/yaml.h>
#include <fstream>
#include <functional>

#include <QFileInfo>
#include <QDir>
#include <QDebug>
#include <QString>

LocalGameData::LocalGameData()
{

}

LocalGameData::~LocalGameData()
{

}

QPixmap LocalGameData::icon() const
{
    return QPixmap( m_iconPath );
}

QString LocalGameData::description() const
{
    return m_description;
}

QString LocalGameData::author() const
{
    return m_author;
}

QString LocalGameData::prettyVersion() const
{
    return m_prettyVersion;
}

int LocalGameData::version() const
{
    return m_version;
}

QString LocalGameData::packId() const
{
    return m_name;
}

IGameData::GameDataTypes LocalGameData::provides() const
{
    return m_dataType;
}

QString LocalGameData::name() const
{
    return m_name;
}

void LocalGameData::parseManifest( const QString& filepath )
{
    //qDebug() << "parseManifest(" <<filepath<<")";
    QFileInfo yaml_info(filepath);
    if( !yaml_info.exists() ) {
        //qDebug() << "manifest doesn't exist";
        m_name = yaml_info.dir().dirName();
        m_author = "Author Unknown";
        m_version = -1;
        m_prettyVersion = "Version Unknown";
        return;
    }
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

    const QString icon_path = yaml_info.absolutePath() + QDir::separator() + "icon.png";
    if( QFileInfo(icon_path).exists() )
        m_iconPath = icon_path;

    doc >> m_dataType;

    qDebug() << "Parsed yaml" << m_name << m_author << m_description << m_version << m_prettyVersion << m_iconPath << m_dataType;

}

void operator>>( const YAML::Node& node, IGameData::GameDataTypes& types )
{
    try {
        const YAML::Node& provides_list = node["provides"];
        for(unsigned i=0;i<provides_list.size();i++) {
            std::string type_std_str;
            provides_list[i] >> type_std_str;
            QString type_str( QString::fromStdString(type_std_str).toLower() );

            if(type_str == "graphics")
                types |= IGameData::Graphics;
            else if(type_str == "tileset")
                types |= IGameData::Tileset;
            else if(type_str == "inits")
                types |= IGameData::Inits;
            else if(type_str == "keybinds")
                types |= IGameData::Keybinds;
        }
    } catch(YAML::RepresentationException& e) {
        qDebug() << "LocalGameData::" << "failed to parse 'provides'";

    }
}


