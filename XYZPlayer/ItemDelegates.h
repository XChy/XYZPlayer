#ifndef ITEMDELEGATES_H
#define ITEMDELEGATES_H

#include <QItemDelegate>
#include <QPainter>
#include <QTime>
#include <QImageReader>

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

class LyricItemDelegate : public QItemDelegate
{
	Q_OBJECT
public:
	LyricItemDelegate(QObject* parent=nullptr);
	void paint(QPainter* painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;//TODO complete it
};

#endif // ITEMDELEGATES_H
