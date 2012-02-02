#include "LocalGraphicsProvider.h"

#include "LocalGraphicsPack.h"

#include <QtilitiesCore>
#include <QDirIterator>
#include <QFileInfo>

LocalGraphicsProvider::LocalGraphicsProvider( const QString &path, QObject *parent )
    : QObject(parent)
    , m_path(path)
{
    QStringList pack_paths = findGraphicsPacks();
    foreach(const QString &path, pack_paths) {
        LocalGraphicsPack* pack = new LocalGraphicsPack(path, this);
        qDebug() << "Found graphics pack" << pack->dataPath() << pack->name();
        OBJECT_MANAGER->registerObject(pack);
    }
}

QStringList LocalGraphicsProvider::findGraphicsPacks() const
{
    QStringList list;
    if( [](QDir dir){ return !dir.exists() || !dir.isReadable();}(QDir(m_path)) ) return list;
    QDirIterator it(m_path, QDir::NoDotAndDotDot | QDir::Dirs);
    while (it.hasNext()) {
        const QString pack_path = it.next();
        if( LocalGraphicsProvider::verifyGraphicsPack( pack_path ) )
            list << pack_path;
    }
    return list;
}

bool LocalGraphicsProvider::verifyGraphicsPack(const QString &path)
{
    const QDir dir(path);
    if( [dir](){ return !dir.exists() || !dir.isReadable();}() ) return false;
    QStringList sub_items = dir.entryList();
    if( sub_items.contains("data") && sub_items.contains("raw") ) {
        return true;
    }
    return false;
}
