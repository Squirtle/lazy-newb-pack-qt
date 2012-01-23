#ifndef GAMEDATAMODEL_H
#define GAMEDATAMODEL_H

#include <QtilitiesCoreGui>

class GameDataModel : public QtilitiesCoreGui::ObserverTreeModel
{
Q_OBJECT
public:
    GameDataModel(QObject *parent = 0);
    virtual ~GameDataModel() {}

    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;
    QVariant data(const QModelIndex &index, int role) const;
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role);
};

#endif // GAMEDATAMODEL_H
