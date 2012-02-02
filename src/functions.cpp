/* functions.h
 * This source file contains various functions which are used throughout the code, along with the StringListModel class.
 */
#include "functions.h"

#include <QDebug>

void getKeybindings(QStringList& list)
{
  //Write to the vector the list of keybinding files
  list.clear();

  QDirIterator it(QObject::tr("./LNP/Keybinds/"), QDir::Files);
  while (it.hasNext())
    {
      list << it.next().remove(QObject::tr("./LNP/Keybinds/"));
    }
  return;
}

QStringList getContents(QString dirname, bool folders)
{
    QStringList list;
    QDirIterator *it;
    if (folders)
        it = new QDirIterator(dirname, QDir::Dirs | QDir::NoDotAndDotDot);
    else
        it = new QDirIterator(dirname, QDir::Files);
    while (it->hasNext())
        list << it->next().remove(dirname);
    return list;
}

// e.g.: cp something/foo /another/place/
// puts 'foo' inside 'place'
void cpDir(QDir from, QDir to)
{
    //qDebug () << "copying" << from.path() << " to " << to.path();
    //TODO: Error handling
    // Check to see if from exists in to, if not we mkdir it
    if( to.entryList( QStringList(from.dirName()), QDir::Dirs).length() == 0 )
        to.mkdir(from.dirName());

    Q_ASSERT( QDir(to.path() + QDir::separator() + from.dirName()).exists() );

    to.cd(from.dirName());
    QFileInfoList entries_list = from.entryInfoList(QDir::NoDotAndDotDot | QDir::Dirs | QDir::Files);
    QListIterator<QFileInfo> source_iterator( entries_list );
    while(source_iterator.hasNext()) {
        const QFileInfo item = source_iterator.next();

        if( item.isDir() ) {
            QDir src_subdir(item.absoluteFilePath());
            QDir dest_subdir(to.path() + QDir::separator() + item.fileName());
            //qDebug() << "src_subdir: " << src_subdir.path() << "dest_subdir: " << dest_subdir.path();

            if( !dest_subdir.exists() )
                to.mkdir(src_subdir.dirName());

            Q_ASSERT(dest_subdir.exists());

            cpDir(src_subdir, to);

        } else if( item.isFile() ) {
            const QString newName( to.absolutePath() + QDir::separator() + item.fileName() );
            // QFile::copy doesn't overwite files, so we must remove them first
            QFile newFile( newName );
            if( newFile.exists() )
                newFile.remove();
            Q_ASSERT(!newFile.exists());
            bool res = QFile::copy(item.absoluteFilePath(), newName);
            Q_ASSERT(res);
            Q_ASSERT(newFile.exists());
        }
    }
}

void rmrfDir(QDir d) {
    QFileInfoList entries_list = d.entryInfoList(QDir::NoDotAndDotDot | QDir::Dirs | QDir::Files);
    QListIterator<QFileInfo> dir_iterator( entries_list );
    while(dir_iterator.hasNext()) {
        const QFileInfo item = dir_iterator.next();

        if( item.isDir() ) {

            QDir subdir(item.absoluteFilePath());
            rmrfDir(subdir);

        } else if( item.isFile() ) {

            QFile file(item.absoluteFilePath());
            file.remove();

        }
    }
    const QString dir_name = d.dirName();
    d.cdUp();
    const bool res = d.rmdir(dir_name);
    Q_ASSERT(res);
    Q_ASSERT(!QDir(d).cd(dir_name));
}

int StringListModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return stringList.count();
}

QVariant StringListModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (index.row() >= stringList.size())
        return QVariant();

    if (role == Qt::DisplayRole)
        return stringList.at(index.row());
    else
        return QVariant();
}

QVariant StringListModel::headerData(int section, Qt::Orientation orientation,
                                     int role) const
{
    if (role != Qt::DisplayRole)
        return QVariant();

    if (orientation == Qt::Horizontal)
        return QString("Column %1").arg(section);
    else
        return QString("Row %1").arg(section);
}

bool StringListModel::removeRows(int row, int count, const QModelIndex &parent)
{
    Q_UNUSED(parent);
    for (int i = row; i < row + count; i++)
    {
       stringList.removeAt(i);
    }
    return true;
} 

bool StringListModel::insertRows(int row, int count, const QModelIndex &parent)
{
    Q_UNUSED(parent);
    for (int i = row; i < row + count; i++)
    {
        stringList.insert(i, "");
    }
    return true;
}

bool StringListModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (!index.isValid())
        return false;

    if (index.row() >= stringList.size())
        return false;

    if (role == Qt::EditRole)
    {
        stringList.replace(index.row(), value.toString());
        return true;
    }

    else
        return false;
}
