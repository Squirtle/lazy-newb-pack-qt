#ifndef LOCALKEYBINDSBUNDLE_H
#define LOCALKEYBINDSBUNDLE_H

#include "IKeybindsBundle.h"
#include "LocalGameData.h"

#include <QObject>

class LocalKeybindsBundle : public QObject, public IKeybindsBundle, public LocalGameData
{
Q_OBJECT
public:
    LocalKeybindsBundle(const QString &path, QObject* parent = nullptr);
    virtual ~LocalKeybindsBundle();

    virtual QString keybindsFilePath();
    virtual bool dataAvailable() const;
    virtual IGameData::GameDataTypes provides() const;

    virtual QObject* objectBase() { return this; }
    virtual const QObject* objectBase() const { return this; }
private:
    QString m_path;
};

#endif // LOCALKEYBINDSBUNDLE_H
