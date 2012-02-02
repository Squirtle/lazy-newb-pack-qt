#ifndef LOCALGRAPHICSPROVIDER_H
#define LOCALGRAPHICSPROVIDER_H

#include "IGraphicsProvider.h"
#include <QObject>

class LocalGraphicsProvider : public QObject, public IGraphicsProvider
{
    Q_OBJECT
    Q_INTERFACES(IGraphicsProvider)
public:
    LocalGraphicsProvider( const QString &path, QObject *parent );
    virtual ~LocalGraphicsProvider(){}

    virtual QObject *objectBase() { return this; }
    virtual const QObject *objectBase() const { return this; }

    /**
      * Checks whether the supplied pack is a valid graphics pack
      */
    static bool verifyGraphicsPack(const QString& path);

private:
    /**
      * Looks one level deep for valid graphics pack.
      * A 'valid' graphics pack is a dir with this structure:
      * dir_name/
      * - data/
      * - raw/
      * - index.dfmod (optional)
      */
    QStringList findGraphicsPacks() const;
    QString m_path;

};

#endif // LOCALGRAPHICSPROVIDER_H
