#include "LocalGraphicsPack.h"

LocalGraphicsPack::LocalGraphicsPack(const QString &path, QObject *parent)
    : QObject(parent)
    , m_path( path )
{
}

LocalGraphicsPack::~LocalGraphicsPack()
{

}

QString LocalGraphicsPack::dataPath() const
{

}

bool LocalGraphicsPack::dataAvailable() const
{

}

QPixmap LocalGraphicsPack::icon() const
{

}

QString LocalGraphicsPack::description() const
{

}

QString LocalGraphicsPack::author() const
{

}

QString LocalGraphicsPack::prettyVersion() const
{

}

int LocalGraphicsPack::version() const
{

}

QString LocalGraphicsPack::packId() const
{

}

QString LocalGraphicsPack::name() const
{

}
