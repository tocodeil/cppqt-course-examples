#include "settingsmodel.h"
#include <QSettings>

SettingsModel::SettingsModel()
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
    if (role == Qt::DisplayRole)
    {
        QSettings settings;
        auto keys = settings.allKeys();
        return keys.at(index.row());
    }
    else
    {
        return QVariant::Invalid;
    }
}

QVariant SettingsModel::headerData(
        int section, Qt::Orientation orientation, int role) const
{
    Q_UNUSED(section);
    Q_UNUSED(orientation);

    if (role == Qt::DisplayRole)
    {
        return QString(tr("Key"));
    }
    return QVariant::Invalid;
}
