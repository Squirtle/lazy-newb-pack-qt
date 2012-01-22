#ifndef LOCALGAMEDATAPROVIDER_H
#define LOCALGAMEDATAPROVIDER_H

#include <QObject>
#include <QString>

class LocalGraphicsProvider;

class LocalGameDataProvider : public QObject
{
public:
    LocalGameDataProvider(const QString & path, QObject *parent = nullptr);
private:
    LocalGraphicsProvider* m_graphicsProvider;
    QString m_path;
};

#endif // LOCALGAMEDATAPROVIDER_H
