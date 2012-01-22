#include "LocalGameDataProvider.h"

#include <QDir>

LocalGameDataProvider::LocalGameDataProvider(const QString & path, QObject *parent)
    : QObject(parent)
    , m_path(path)
{
    QDir dir(m_path);
    if(!dir.exists()) { /* TODO */ }


}
