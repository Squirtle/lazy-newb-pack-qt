#include "DwarfFortress.h"

#include <QDirIterator>
#include <QDebug>
#include <QApplication>

DwarfFortress::DwarfFortress() : QObject( 0 )
{
    QString dfFolder;
    // Find location of DF installation
   dfFolder = findInstallation(".", "Dwarf Fortress");

   if( dfFolder.isEmpty() ) {
       // find /opt installation, ArchLinux installs here
       dfFolder = findInstallation("/opt");
   }

   //TODO: search in more locations, where do other distros put their DFs?
   qDebug() << "DF PATH" << dfFolder;
   m_dfFolder = dfFolder;
   m_hasDF = !m_dfFolder.isEmpty();
}

QString DwarfFortress::findInstallation(const QString &path, const QString &folder_name)
{
    //TODO: verify the folder found is actually a DF install
    QString DFFolderName;
    QDirIterator it(path, QDir::NoDotAndDotDot | QDir::Dirs);
    while (it.hasNext()) {
        DFFolderName = it.next();
        if (DFFolderName.contains(folder_name)) {
            return DFFolderName;
        }
    }
    return QString();
}

bool DwarfFortress::hasDF() const
{
    return m_hasDF;
}

QString DwarfFortress::getDFFolder() const
{
    return m_dfFolder;
}

void DwarfFortress::setDFFolder(const QString & path)
{
    //TODO: verify path
    if( path != m_dfFolder ) {
        m_dfFolder = path;
        m_hasDF = !m_dfFolder.isEmpty();
        emit dataChanged();
    }
}

QString DwarfFortress::getDInitPath() const
{
    return m_dfFolder + "/data/init/d_init.txt";
}

QString DwarfFortress::getInitPath() const
{
    return m_dfFolder + "/data/init/init.txt";
}

QString DwarfFortress::getInterfacePath() const
{
    return m_dfFolder + "/data/init/interface.txt";
}

QString DwarfFortress::getSavePath() const
{
    return m_dfFolder + "/data/save/";
}

QString DwarfFortress::getRawObjectsPath() const
{
    return m_dfFolder + "/raw/objects/";
}

QString DwarfFortress::getArtDir() const
{
    return m_dfFolder + "/data/art";
}

QString DwarfFortress::getOption(const QString &option) const
{
  QFile init(getInitPath());
  QFile dinit(getDInitPath());

  init.open(QIODevice::ReadOnly | QIODevice::Text);
  dinit.open(QIODevice::ReadOnly | QIODevice::Text);
  //TODO: Add failure exceptions

  QString text;
  text = init.readAll();
  text += dinit.readAll();

  init.close();
  dinit.close();

  const int idxOpt = text.indexOf("[" + option + ":");

  return text.mid( idxOpt + option.size() + 2,
                  text.indexOf("]", idxOpt) - idxOpt - option.size() - 2);
}


void DwarfFortress::setOption(const QString &option, const QString &newValue)
{
  //Set option's value to newValue

  QFile init(getInitPath());
  QFile dinit(getDInitPath());

  dinit.open(QIODevice::ReadOnly | QIODevice::Text);
  //TODO: Add failure exceptions

  QString* buffer;
  buffer = new QString(dinit.readAll());
  dinit.close();

  int idxOpt = buffer->indexOf("[" + option + ":");
  int idxClose = buffer->indexOf("]", idxOpt);
  const int szOpt = ("[" + option + ":").size();
  if ((idxOpt != -1) && (idxClose != -1)) {
        int begin_option = idxOpt + szOpt;
        int option_length = idxClose - (idxOpt + szOpt);
        buffer->remove(begin_option, option_length);
        buffer->insert(begin_option, newValue);
        dinit.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate);
        dinit.write(buffer->toAscii());
        dinit.close();
    } else {
        delete buffer;
        dinit.close();
        init.open(QIODevice::ReadOnly | QIODevice::Text);
        buffer = new QString(init.readAll());
        init.close();

        idxOpt = buffer->indexOf("[" + option + ":");
        idxClose = buffer->indexOf("]", idxOpt);

        int begin_option = idxOpt + szOpt;
        int option_length = idxClose - (idxOpt + szOpt);
        buffer->remove(begin_option, option_length);
        buffer->insert(begin_option, newValue);
        init.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate);
        init.write(buffer->toAscii());
        init.close();
    }
    delete buffer;
}

QString DwarfFortress::rawsFind(const QString &find) const
{
    QVector<QString> rawList;
    QDirIterator it(getRawObjectsPath(), QDir::Files);
    while (it.hasNext()) {
        rawList.push_back(it.next());
    }

    QFile rawFile;

    foreach (QString i, rawList) {
        rawFile.setFileName(i);
        rawFile.open(QIODevice::ReadOnly | QIODevice::Text);
        QString temp(rawFile.readAll());
        rawFile.close();
        if (temp.contains(find))
            return "YES";
    }
    return "NO";
}

void DwarfFortress::rawsReplace(const QString &old, const QString &replaced)
{
  QVector<QString> rawList;
  QDirIterator it(getRawObjectsPath(), QDir::Files);
  while (it.hasNext())
    {
        rawList.push_back(it.next());
    }

  QFile rawFile;
  QString* buffer;

  foreach (QString i, rawList)
    {
      rawFile.setFileName(i);
      rawFile.open(QIODevice::ReadOnly | QIODevice::Text);
      buffer = new QString(rawFile.readAll());
      rawFile.close();
      buffer->replace(old, replaced);
      rawFile.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate);
      rawFile.write(buffer->toAscii());
      rawFile.close();
      delete buffer;
    }
  return;
}

void DwarfFortress::notifyChange()
{
    emit dataChanged();
}
