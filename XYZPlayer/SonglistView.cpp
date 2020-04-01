#include "SonglistView.h"

SonglistView::SonglistView(QWidget* parent)
	:QTableView(parent),
	  _popupMenu(new QMenu(this))
{
	setDragDropMode(QAbstractItemView::DragDrop);
	setDragEnabled(true);
	setDropIndicatorShown(true);

	verticalHeader()->setVisible(false);
	setSelectionBehavior(QAbstractItemView::SelectRows);
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
