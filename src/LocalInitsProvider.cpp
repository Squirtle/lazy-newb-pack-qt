#include "LocalInitsProvider.h"

#include "InitsBundle.h"

#include <QtilitiesCore>
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
        InitsBundle* pack = new InitsBundle(path, this);
        qDebug() << "LocalInitsProvider:: found inits" << pack->name() << pack->initPath();
        OBJECT_MANAGER->registerObject(pack);
    }
}

QStringList LocalInitsProvider::findInitsPacks() const
{
    QStringList list;
    if( [](QDir dir){ return !dir.exists() || !dir.isReadable();}(QDir(m_path)) ) return list;
    QDirIterator it(m_path, QDir::NoDotAndDotDot | QDir::Dirs);
    while (it.hasNext()) {
        const QString dir( it.next() );
        if( LocalInitsProvider::verifyInitsPack( dir ) )
            list << dir;
    }
    return list;
}

bool LocalInitsProvider::verifyInitsPack(const QString &path)
{
    const QDir dir(path);
    if( [dir](){ return !dir.exists() || !dir.isReadable();}() ) return false;
    QStringList sub_items = dir.entryList(QDir::Files);
    //TODO: what happens when there is more than one thing?
    if( sub_items.size() > 3 /* third is possible manifest */ ) qWarning() << "LocalInitsProvider::verifyInitsPack.. possible something else ?" << path;
    if( sub_items.contains("init.txt") && sub_items.contains("d_init.txt") ) {
        return true;
    }
    return false;
}
