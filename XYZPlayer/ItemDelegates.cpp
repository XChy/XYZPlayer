#include "ItemDelegates.h"
#include <QDebug>

PlayingItemDelegate::PlayingItemDelegate(QObject* parent)
	:QItemDelegate(parent)
{}

void PlayingItemDelegate::paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const
{
	drawBackground(painter,option,index);
	if(index.data().toBool()){
		painter->drawImage(option.rect,QImage(":/images/easy/playing.png"));
	}
}

TextItemDelegate::TextItemDelegate(QObject* parent)
	:QItemDelegate(parent)
{}

void TextItemDelegate::paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const
{
	drawDisplay(painter,option,option.rect,elidedText(option.fontMetrics,option.rect.width(),Qt::ElideRight,index.data().toString()));
}

DurationItemDelegate::DurationItemDelegate(QObject* parent)
	:QItemDelegate(parent)
{}

void DurationItemDelegate::paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const
{
	int64_t duration=index.data().toLongLong();
	drawDisplay(painter,option,option.rect,QTime(0,0).addSecs(duration/1000000).toString("m:ss"));
}
