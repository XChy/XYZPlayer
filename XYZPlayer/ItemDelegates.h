#ifndef ITEMDELEGATES_H
#define ITEMDELEGATES_H

#include <QItemDelegate>
#include <QPainter>
#include <QTime>

class PlayingItemDelegate : public QItemDelegate
{
	Q_OBJECT
public:
	PlayingItemDelegate(QObject* parent=nullptr);
	void paint(QPainter* painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
};

class TextItemDelegate : public QItemDelegate
{
	Q_OBJECT
public:
	TextItemDelegate(QObject* parent=nullptr);
	void paint(QPainter* painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
};

class DurationItemDelegate : public QItemDelegate
{
	Q_OBJECT
public:
	DurationItemDelegate(QObject* parent=nullptr);
	void paint(QPainter* painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
};


#endif // ITEMDELEGATES_H
