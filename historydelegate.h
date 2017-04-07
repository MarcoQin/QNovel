#ifndef HISTORYDELEGATE_H
#define HISTORYDELEGATE_H
#include <QStyledItemDelegate>

class HistoryDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    HistoryDelegate(QWidget *parent = 0) : QStyledItemDelegate(parent) {}

    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const Q_DECL_OVERRIDE;
};

#endif // HISTORYDELEGATE_H
