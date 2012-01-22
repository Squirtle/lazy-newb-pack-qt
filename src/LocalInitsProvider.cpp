#include "LocalInitsProvider.h"

#include <QDir>
#include <QDirIterator>
#include <QDebug>

LocalInitsProvider::LocalInitsProvider( const QString& path, QObject* parent )
: QObject( parent )
, m_path( path )
{
    QDir dir(m_path);
    if(!dir.exists()) { qWarning() << "LocalInitsProvider:: path doesn't exist" << path; /* TODO: handle */ }

    QStringList pack_paths = findInitsPacks();
    foreach(const QString &path, pack_paths) {
        /*LocalGraphicsPack* pack = new LocalGraphicsPack(path, this);
        OBJECT_MANAGER->registerObject(pack);*/
    }
}

QStringList LocalInitsProvider::findInitsPacks() const
{
    QStringList list;
    if( [](QDir dir){ return !dir.exists() || !dir.isReadable();}(QDir(m_path)) ) return list;
    QDirIterator it(m_path, QDir::NoDotAndDotDot | QDir::Dirs);
    while (it.hasNext()) {
        if( LocalInitsProvider::verifyInitsPack( it.next() ) )
            list << it.path();
    }
    return list;
}

bool LocalInitsProvider::verifyInitsPack(const QString &path)
{
    const QDir dir(path);
    if( [dir](){ return !dir.exists() || !dir.isReadable();}() ) return false;
    QStringList sub_items = dir.entryList();
    if( sub_items.contains("init.txt") && sub_items.contains("d_init.txt") ) {
        qDebug() << "Found graphics pack: " << path;
        return true;
    }
    return false;
}
