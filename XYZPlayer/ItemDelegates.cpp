#include "ItemDelegates.h"

void DurationItemDelegate::paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const
{
	int64_t duration=index.data().toLongLong();
	drawDisplay(painter,option,option.rect,QTime().addSecs(duration/(10*6)).toString("mm:ss"));
}
