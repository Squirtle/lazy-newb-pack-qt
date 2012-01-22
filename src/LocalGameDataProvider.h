#ifndef LOCALGAMEDATAPROVIDER_H
#define LOCALGAMEDATAPROVIDER_H

#include <QObject>
#include <QString>

class LocalGameDataProvider : public QObject
{
public:
    LocalGameDataProvider(const QString & path, QObject *parent = nullptr);
private:
    QString m_path;
};

#endif // LOCALGAMEDATAPROVIDER_H
