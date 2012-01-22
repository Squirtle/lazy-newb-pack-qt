#ifndef LOCALGRAPHICSPACK_H
#define LOCALGRAPHICSPACK_H

#include "IGraphicsPack.h"

#include <QString>

class LocalGraphicsPack : public QObject, public IGraphicsPack
{

public:
    LocalGraphicsPack(const QString &path, QObject *parent);
    virtual ~LocalGraphicsPack();

    virtual QString dataPath() const;
    virtual bool dataAvailable() const;
    virtual QPixmap icon() const;
    virtual QString description() const;
    virtual QString author() const;
    virtual QString prettyVersion() const;
    virtual int version() const;
    virtual QString packId() const;
    virtual QString name() const;

private:
    void parseIndex();
    QString m_path;
    QString m_name;
    QString m_author;
    QString m_prettyVersion;
    int m_version;
    QString m_description;
    QString m_iconPath;
};

#endif // LOCALGRAPHICSPACK_H
