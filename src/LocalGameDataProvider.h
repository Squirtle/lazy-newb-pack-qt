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
    QString m_path;
    LocalGraphicsProvider* m_graphicsProvider;
};

#endif // LOCALGAMEDATAPROVIDER_H
