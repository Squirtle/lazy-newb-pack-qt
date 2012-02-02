#ifndef LOCALGRAPHICSPACK_H
#define LOCALGRAPHICSPACK_H

#include "IGraphicsPack.h"
#include "LocalGameData.h"

#include <QString>

class LocalGraphicsPack : public QObject, public IGraphicsPack, public LocalGameData
{
Q_OBJECT
Q_INTERFACES(IGraphicsPack);
public:
    LocalGraphicsPack(const QString &path, QObject *parent = nullptr);
    virtual ~LocalGraphicsPack();

    virtual QString dataPath() const;
    virtual bool dataAvailable() const;
    virtual GameDataTypes provides() const;

    QObject* objectBase() { return this; }
    const QObject* objectBase() const { return this; }

private:
    QString m_path;

};

#endif // LOCALGRAPHICSPACK_H
