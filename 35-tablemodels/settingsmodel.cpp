#include "settingsmodel.h"
#include <QSettings>

SettingsModel::SettingsModel(QObject *parent):
    QAbstractTableModel(parent)
{

}


int SettingsModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);

    QSettings settings;
    return settings.allKeys().size();
}

QVariant SettingsModel::data(const QModelIndex &index, int role) const
{
    if ((role == Qt::DisplayRole)||(role == Qt::EditRole))
    {
        QSettings settings;
        auto keys = settings.allKeys();
        auto key = keys.at(index.row());
        if (index.column() == 0)
        {
            return key;
        }
        else if (index.column() == 1)
        {
            return settings.value(key);
        }
    }
    return QVariant::Invalid;
}

QVariant SettingsModel::headerData(
        int section, Qt::Orientation orientation, int role) const
{
    if ((role == Qt::DisplayRole) && orientation == Qt::Horizontal)
    {
        if (section == 0)
        {
            return QString(tr("Key"));
        }
        else if (section == 1)
        {
            return QString(tr("Value"));
        }
    }

    return QVariant::Invalid;
}


int SettingsModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return 2;
}


bool SettingsModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    Q_UNUSED(role);

    QSettings settings;
    auto key = data(this->index(index.row(), 0), Qt::DisplayRole).toString();

    settings.setValue(key, value);

    return true;
}

Qt::ItemFlags SettingsModel::flags(const QModelIndex &index) const
{
    if (index.column() == 1)
    {
        return QAbstractItemModel::flags(index) | Qt::ItemIsEditable;
    }
    else
    {
        return QAbstractItemModel::flags(index);
    }

}


bool SettingsModel::removeRows(int row, int count, const QModelIndex &parent)
{
    Q_UNUSED(parent);
    beginRemoveRows(parent, row, row + count - 1);
    QSettings settings;
    auto keys = settings.allKeys();
    for (int i=0; i < count; i++)
    {
        auto k = keys.at(row + i);
        settings.remove(k);
    }
    endRemoveRows();

    return true;
}

bool SettingsModel::addSetting(QString key, QVariant val)
{
    if (key.isEmpty() || val.toString().isEmpty())
    {
        return false;
    }

    beginResetModel();
    QSettings settings;
    settings.setValue(key, val);
    settings.sync();

    endResetModel();
    return true;
}







