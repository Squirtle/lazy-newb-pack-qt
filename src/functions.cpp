/* functions.hpp
 * This source file contains various functions which are used throughout the code, along with the StringListModel class.
 */
#include "functions.hpp"

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

bool copyFile(QFile &file1, QFile &file2)
{
    bool ok1 = file1.open(QFile::ReadOnly);
    QByteArray *buffer = new QByteArray(file1.readAll());
    file1.close();
    bool ok2 = file2.open(QFile::WriteOnly | QFile::Truncate);
    file2.write(*buffer);
    file2.close();
    delete buffer;
    return ok1 && ok2;
}

void cpDir1(QDir from, QStringList &list)
{
    QStringList filelist = from.entryList(QDir::NoDotAndDotDot | QDir::Dirs | QDir::Files);

    foreach (QString file, filelist)
    {
        QFileInfo info(QString("%1/%2").arg(from.path()).arg(file));

        if (info.isDir())
        {
            QDir newdir(info.filePath());
            cpDir1(info.filePath(), list);
        }
        else
            list << QDir::toNativeSeparators(info.filePath());
    }
}

void cpDir2(QDir from, QDir to, QStringList list)
{
    //TODO: Error handling
    foreach (QString file, list)
    {
        QFile filefrom(file);
        QFile fileto(to.path() + file.remove(0, from.path().length()));
        copyFile(filefrom, fileto);
    }
}

void cpDir(QDir from, QDir to)
{
    //TODO: Error handling
    QStringList list;
    cpDir1(from, list);
    cpDir2(from, to, list);
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
