#ifndef LOCALINITSPROVIDER_H
#define LOCALINITSPROVIDER_H


#include "IInitsProvider.h"

#include <QObject>

/**
 * Provides Init files (init.txt and d_init.txt) in the LNP style of
 * a_directory/
 * - init.txt
 * - d_init.txt
 */
class LocalInitsProvider : public QObject, public IInitsProvider
{
    Q_OBJECT
    Q_INTERFACES(IInitsProvider)
public:
    LocalInitsProvider(const QString &path, QObject *parent = nullptr);
    virtual ~LocalInitsProvider(){}

    virtual QObject* objectBase() { return this; }
    virtual const QObject* objectBase() const { return this; }

    virtual QString dinitPath();
    virtual QString initPath();

private:
    QStringList findInitsPacks() const;
    static bool verifyInitsPack(const QString &path);

    QString m_path;
};

#endif // LOCALINITSPROVIDER_H
