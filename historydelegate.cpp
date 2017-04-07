#include "historydelegate.h"
#include <QDebug>
#include <QPainter>
#include <QtWidgets>

void HistoryDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QString s = qvariant_cast<QString>(index.data());

    QStringList l = s.split("\n");
    QString name = (QString) l.at(0);
    QString left = (QString) l.at(1);
    QString path = (QString) left.split("#").at(0);

    painter->save();

    if (option.state & QStyle::State_Selected) {
        painter->fillRect(option.rect, option.palette.highlight());
        painter->setPen(QColor(200, 200, 200));
    } else {
        painter->setPen(QColor(0, 0, 0));
    }
    painter->drawText(option.rect, name);

    painter->setPen(QColor(92, 170, 56));
    painter->drawText(option.rect.x(), option.rect.y() + option.rect.height()/2 + 10, path);

    painter->restore();
}
