#ifndef ITEMDELEGATES_H
#define ITEMDELEGATES_H

#include <QItemDelegate>
#include <QTime>

class DurationItemDelegate : public QItemDelegate
{
	Q_OBJECT
public:
	DurationItemDelegate(QObject* parent=nullptr);
	void paint(QPainter* painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
};

#endif // ITEMDELEGATES_H
