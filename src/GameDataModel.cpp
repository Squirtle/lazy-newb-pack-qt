#include "GameDataModel.h"

#include "IGameData.h"

GameDataModel::GameDataModel( QObject* parent ): ObserverTableModel( parent )
{

}

QVariant GameDataModel::data(const QModelIndex &index, int role) const {
    return ObserverTableModel::data(index, role);
    if (role == Qt::DisplayRole) {
        QObject* obj = getObject(1);
        if (obj) {
            IGameData* gamedata= qobject_cast<IGameData*> (obj);
            if(gamedata)
                return gamedata->name();
        }
    }
    return QVariant();
}

int GameDataModel::columnCount( const QModelIndex& parent ) const
{
    return Qtilities::CoreGui::ObserverTableModel::columnCount( parent );
}

QVariant GameDataModel::headerData( int section, Qt::Orientation orientation, int role ) const
{
    return Qtilities::CoreGui::ObserverTableModel::headerData( section, orientation, role );
}

int GameDataModel::rowCount( const QModelIndex& parent ) const
{
    return Qtilities::CoreGui::ObserverTableModel::rowCount( parent );
}

bool GameDataModel::setData( const QModelIndex& index, const QVariant& value, int role )
{
    return Qtilities::CoreGui::ObserverTableModel::setData( index, value, role );
}
