#include "LocalGraphicsProvider.h"


#include <QDirIterator>
#include <QFileInfo>

LocalGraphicsProvider::LocalGraphicsProvider( const QString &path, QObject *parent )
    : QObject(parent)
    , m_path(path)
{
    QStringList pack_paths = findGraphicsPacks();
    foreach(const QString &path, pack_paths) {
    }
}

QStringList LocalGraphicsProvider::findGraphicsPacks() const
{
    QStringList list;
    if( [](QDir dir){ return dir.exists() && dir.isReadable();}(QDir(m_path)) ) return list;
    QDirIterator it(m_path, QDir::NoDotAndDotDot | QDir::Dirs);
    while (it.hasNext()) {
        QDir sub_dir(it.next());
        QStringList sub_sub_items = sub_dir.entryList();
        if( sub_sub_items.contains("data") && sub_sub_items.contains("raw") )
            list << sub_dir.path();
    }
    return list;
}
