#include "IconLoader.h"

#include <QFile>
#include <QDebug>

QIcon IconLoader::load(const QString &name)
{
    if(name.isEmpty()) return QIcon();
    QIcon icon;

    if (!QIcon::hasThemeIcon(name)) {
        QIcon::setThemeName("fallback");
    }
    icon = QIcon::fromTheme(name);
    qDebug() << icon.isNull();
    if(!icon.isNull()) return icon;
/*
    // Fallback

    const QString path(":/%1x%2/%3.png");
    for (int size : _sizes) {
      QString filename(path.arg(size).arg(size).arg(name));
      qDebug() << filename;
      if(QFile::exists(filename))
          qDebug() << "BOOYA";
          icon.addFile(filename, QSize(size, size));
          icon = QIcon(filename);
    }

    if(icon.isNull())
      qDebug() << "Couldn't load icon" << name;*/
    return icon;
}
