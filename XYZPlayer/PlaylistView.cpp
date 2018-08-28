#include "PlaylistView.h"

PlaylistView::PlaylistView(QWidget* parent)
	:QTableView(parent)
	,mPopupMenu(new QMenu(this))
{
	setDragDropMode(QAbstractItemView::DragDrop);
	setDragEnabled(true);
	setDropIndicatorShown(true);

	verticalHeader()->setVisible(false);
	horizontalHeader()->setVisible(false);

	mPopupMenu->addAction(tr("Play"),[&](){
		model()->player()->playAt(selectionModel()->currentIndex().row());
	});
	mPopupMenu->addAction(tr("Copy title"),[&](){
		QApplication::clipboard()->setText(
					model()->player()->playlist()[selectionModel()->currentIndex().row()].d->infoTags["title"]
				);
	});
	mPopupMenu->addAction(tr("Copy artist"),[&](){
		QApplication::clipboard()->setText(
					model()->player()->playlist()[selectionModel()->currentIndex().row()].d->infoTags["artist"]
				);
	});
	mPopupMenu->addAction(tr("Copy album"),[&](){
		QApplication::clipboard()->setText(
					model()->player()->playlist()[selectionModel()->currentIndex().row()].d->infoTags["album"]
				);
	});
	mPopupMenu->addAction(tr("Remove"),[&](){
		int offset=0;
		for(QModelIndex& index:selectionModel()->selectedRows()){
			model()->player()->removeMusic(index.row()-offset);
			++offset;
		}
	});

	setSelectionBehavior(QAbstractItemView::SelectRows);
}

void PlaylistView::contextMenuEvent(QContextMenuEvent* e)
{
	QPoint pos=e->pos();
	QModelIndex index=indexAt(pos);
	if(index.isValid()){
		if(selectionModel()->hasSelection()){
			if(!selectionModel()->isSelected(index)){
				selectionModel()->setCurrentIndex(index,QItemSelectionModel::ClearAndSelect|QItemSelectionModel::Rows);
			}
			mPopupMenu->exec(e->globalPos());
			e->accept();
		}else{
			selectionModel()->setCurrentIndex(indexAt(pos),QItemSelectionModel::Select|QItemSelectionModel::Rows);
			mPopupMenu->exec(e->globalPos());
			e->accept();
		}
	}
}

void PlaylistView::mouseDoubleClickEvent(QMouseEvent* e)
{
	QModelIndex index=indexAt(e->pos());
	if(index.isValid()){
		model()->player()->playAt(index.row());
	}
}

void PlaylistView::setModel(PlaylistModel* model)
{
	QTableView::setModel(model);
}

PlaylistModel* PlaylistView::model()
{
	return qobject_cast<PlaylistModel*>(QTableView::model());
}
