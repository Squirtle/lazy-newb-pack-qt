#include "GameDataModel.h"

#include "IGameData.h"

GameDataModel::GameDataModel( QObject* parent ): ObserverTreeModel( parent )
{

}

QVariant GameDataModel::data(const QModelIndex &index, int role) const {
    if ((index.column() == columnCount() - 1) && (role == Qt::DisplayRole)) {
        QObject* obj = getObject(index);
        if (obj) {
            IGameData* gamedata= qobject_cast<IGameData*> (obj);
            if(gamedata)
                return gamedata->name();
        }
        return QVariant();
    } else {
        return ObserverTreeModel::data(index,role);
    }
}

int GameDataModel::columnCount( const QModelIndex& parent ) const
{
    return Qtilities::CoreGui::ObserverTreeModel::columnCount( parent );
}

QVariant GameDataModel::headerData( int section, Qt::Orientation orientation, int role ) const
{
    return Qtilities::CoreGui::ObserverTreeModel::headerData( section, orientation, role );
}

int GameDataModel::rowCount( const QModelIndex& parent ) const
{
    return Qtilities::CoreGui::ObserverTreeModel::rowCount( parent );
}

bool GameDataModel::setData( const QModelIndex& index, const QVariant& value, int role )
{
    return Qtilities::CoreGui::ObserverTreeModel::setData( index, value, role );
}
