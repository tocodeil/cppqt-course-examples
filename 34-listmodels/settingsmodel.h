#ifndef SETTINGSMODEL_H
#define SETTINGSMODEL_H

#include <QAbstractListModel>

class SettingsModel : public QAbstractListModel
{
public:
    SettingsModel();

    // QAbstractItemModel interface
public:
    virtual int rowCount(const QModelIndex &parent) const;
    virtual QVariant data(const QModelIndex &index, int role) const;
    virtual QVariant headerData(int section, Qt::Orientation orientation, int role) const;
};

#endif // SETTINGSMODEL_H
