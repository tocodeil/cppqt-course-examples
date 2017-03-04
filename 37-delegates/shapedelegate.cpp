#include "shapedelegate.h"
#include <QPainter>
#include <QPainterPath>
#include <QtMath>
#include <QSpinBox>

ShapeDelegate::ShapeDelegate(QObject *parent): QStyledItemDelegate(parent)
{

}


void ShapeDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(option);
    int edges = index.data(Qt::DisplayRole).toString().toInt();
    QPainterPath path;
    int r = qMin(option.rect.height()/3, option.rect.width()/3);
    painter->save();
    painter->translate(option.rect.center().x(), option.rect.center().y());

    for (int n=0; n <= edges; n++)
    {
        auto x = r * cos(2*M_PI*n/edges);
        auto y = r * sin(2*M_PI*n/edges);
        if (n>0) path.lineTo(x, y);
        path.moveTo(x, y);
    }
    painter->drawPath(path);
    painter->restore();
}

QSize ShapeDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(option);
    Q_UNUSED(index);
    return QSize(100, 100);
}


QWidget *ShapeDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(option);
    Q_UNUSED(index);
    return new QSpinBox(parent);;
}

void ShapeDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    QSpinBox *box = qobject_cast<QSpinBox *>(editor);
    if (!box) return;

    box->setValue(index.data().toString().toInt());
}

void ShapeDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    QSpinBox *box = qobject_cast<QSpinBox *>(editor);
    if (!box) return;

    model->setData(index, box->value());
}

void ShapeDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(index);
    editor->setGeometry(option.rect);
}
