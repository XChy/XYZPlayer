#include "SonglistsView.h"

SonglistsView::SonglistsView(QWidget *parent) :
	QListView(parent),
	_popupMenu(new QMenu(this))
{
	setViewMode(IconMode);
	setIconSize(QSize(80,80));
	setGridSize(QSize(90,90));
	setResizeMode(Adjust);

	setDragDropMode(QAbstractItemView::DragDrop);
	setDragEnabled(true);
	setDropIndicatorShown(true);
}

void SonglistsView::contextMenuEvent(QContextMenuEvent* e)
{
	QPoint pos=e->pos();
	QModelIndex index=indexAt(pos);
	if(index.isValid()){
		if(selectionModel()->hasSelection()){
			if(!selectionModel()->isSelected(index)){
				selectionModel()->setCurrentIndex(index,QItemSelectionModel::ClearAndSelect);
			}
			_popupMenu->exec(e->globalPos());
			e->accept();
		}else{
			selectionModel()->setCurrentIndex(indexAt(pos),QItemSelectionModel::Select);
			_popupMenu->exec(e->globalPos());
			e->accept();
		}
	}
}

void SonglistsView::mouseDoubleClickEvent(QMouseEvent* e)
{

}

QMimeData* SonglistsView::mimeData(const QModelIndexList& indexes) const
{

}

void SonglistsView::setModel(SonglistsModel* model)
{
	QListView::setModel(model);
}

SonglistsModel* SonglistsView::model()
{
	return (SonglistsModel*)QListView::model();
}
