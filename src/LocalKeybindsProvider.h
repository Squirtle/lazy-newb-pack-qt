#ifndef LOCALKEYBINDSPROVIDER_H
#define LOCALKEYBINDSPROVIDER_H

#include "IGameData.h"

#include <QObject>
#include <QString>

class LocalKeybindsProvider : public QObject
{
Q_OBJECT
public:
    LocalKeybindsProvider( const QString &path, QObject* parent = nullptr );
    virtual ~LocalKeybindsProvider(){}

    static bool verifyKeybinds(const QString &path);
private:
    QStringList findKeybinds() const;

    QString m_path;
};

#endif // LOCALKEYBINDSPROVIDER_H
