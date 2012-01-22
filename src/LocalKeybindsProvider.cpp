#include "LocalKeybindsProvider.h"

#include "LocalKeybindsBundle.h"

#include <QtilitiesCore>
#include <QDir>

LocalKeybindsProvider::LocalKeybindsProvider( const QString& path, QObject* parent )
    :QObject(parent)
    , m_path(path)
{
    QDir dir(m_path);
    if(!dir.exists()) { qWarning() << "LocalKeybindsProvider:: path doesn't exist" << path; /* TODO: handle */ }

    QStringList pack_paths = findKeybinds();
    foreach(const QString &path, pack_paths) {
        LocalKeybindsBundle* pack = new LocalKeybindsBundle(path, this);
        qDebug() << "LocalKeybindsProvider:: found keybinds" << pack->name() << pack->keybindsFilePath();
        OBJECT_MANAGER->registerObject(pack);
    }
}

QStringList LocalKeybindsProvider::findKeybinds() const
{
    QStringList list;
    if( [](QDir dir){ return !dir.exists() || !dir.isReadable();}(QDir(m_path)) ) return list;
    QDirIterator it(m_path, QStringList() << "*.txt", QDir::Files);
    while (it.hasNext()) {
        const QString txt_file( it.next() );
        if( LocalKeybindsProvider::verifyKeybinds( txt_file ) )
            list << txt_file;
    }
    return list;
}

bool LocalKeybindsProvider::verifyKeybinds(const QString &path)
{
    QFile keybinds(path);
    bool result = keybinds.open(QIODevice::ReadOnly);
    if(!result) return result;

    const QString pattern( "[BIND:SELECT:REPEAT_NOT]" );
    while(!keybinds.atEnd()) {
        const QString line( keybinds.readLine().trimmed().toUpper() );
        if( line.compare(pattern) == 0 ) {
            return true;
        }
    }
    return false;
}


