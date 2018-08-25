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

class TitleItemDelegate : public QItemDelegate
{
	Q_OBJECT
public:
	TitleItemDelegate(QObject* parent=nullptr);
	void paint(QPainter* painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
};

class ArtistItemDelegate : public QItemDelegate
{
	Q_OBJECT
public:
	ArtistItemDelegate(QObject* parent=nullptr);
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
