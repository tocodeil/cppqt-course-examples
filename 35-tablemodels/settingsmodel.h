#ifndef SETTINGSMODEL_H
#define SETTINGSMODEL_H

#include <QAbstractListModel>

class SettingsModel : public QAbstractTableModel
{
public:
    SettingsModel(QObject *parent);

    // QAbstractItemModel interface
public:
    virtual int rowCount(const QModelIndex &parent) const;
    virtual QVariant data(const QModelIndex &index, int role) const;
    virtual QVariant headerData(int section, Qt::Orientation orientation, int role) const;

    // QAbstractItemModel interface
public:
    virtual int columnCount(const QModelIndex &parent) const;

    // QAbstractItemModel interface
public:
    virtual bool setData(const QModelIndex &index, const QVariant &value, int role);
    virtual Qt::ItemFlags flags(const QModelIndex &index) const;

    // QAbstractItemModel interface
public:
    virtual bool removeRows(int row, int count, const QModelIndex &parent);

public:
    bool addSetting(QString key, QVariant val);
};

#endif // SETTINGSMODEL_H
