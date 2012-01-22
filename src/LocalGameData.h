#ifndef LOCALGAMEDATA_H
#define LOCALGAMEDATA_H

#include "IGameData.h"

namespace YAML {
    class Node;
}

class LocalGameData : public virtual IGameData
{

public:
    LocalGameData();
    virtual ~LocalGameData();

    virtual QPixmap icon() const;
    virtual QString description() const;
    virtual QString author() const;
    virtual QString prettyVersion() const;
    virtual int version() const;
    virtual QString packId() const;
    virtual GameDataTypes provides() const;
    virtual QString name() const;

protected:
    /**
     * Path to the yaml file or the dir containing it
     * @param filepath a dir or a file to parse the manifest from
     * @param useFileNameAsName if filepath is a file and this is true, then the the name of the file with the yaml extension will be loaded instead of index.yaml
     * For example if a keybinds file is named "MySuperKeybinds.txt" and that is passed as filepath,
     * then if useFileNameAsName is true, this method will attempt to parse MySuperKeybinds.yaml IN THE SAME DIRECTORY as
     * MySuperKeybinds.txt
     */
    void parseManifest(const QString &filepath, bool useFileNameAsName = false);

private:
    QString m_name;
    QString m_author;
    QString m_prettyVersion;
    int m_version;
    QString m_description;
    QString m_iconPath;
    IGameData::GameDataTypes m_dataType;
};

void operator >> (const YAML::Node& node, IGameData::GameDataTypes& types);

#endif // LOCALGAMEDATA_H
