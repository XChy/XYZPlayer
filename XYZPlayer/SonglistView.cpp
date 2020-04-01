#include "SonglistView.h"

SonglistView::SonglistView()
	:_popupMenu(new QMenu(this))
{

}

void SonglistView::contextMenuEvent(QContextMenuEvent* e)
{

}

void SonglistView::mouseDoubleClickEvent(QMouseEvent* e)
{

}

SonglistModel* SonglistView::model() const
{
	return (SonglistModel*)QTableView::model();
}

void SonglistView::setModel(SonglistModel* model)
{
	QTableView::setModel(model);
}
