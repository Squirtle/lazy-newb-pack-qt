#ifndef LOCALKEYBINDSPROVIDER_H
#define LOCALKEYBINDSPROVIDER_H

#include "IGameData.h"

#include <QObject>
#include <QString>

class QFileSystemWatcher;

class LocalKeybindsProvider : public QObject
{
Q_OBJECT
public:
    LocalKeybindsProvider( const QString &path, QObject* parent = nullptr );
    virtual ~LocalKeybindsProvider(){}

    static bool verifyKeybinds(const QString &path);

private slots:
    void keybindsDirChanged();

private:
    void addKeybinds();
    QStringList findKeybinds() const;

    QString m_path;
    QFileSystemWatcher* m_fsWatcher;
};

#endif // LOCALKEYBINDSPROVIDER_H
