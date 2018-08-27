#include "PlaylistView.h"

PlaylistView::PlaylistView(QWidget* parent)
	:QTableView(parent)
	  ,mPopupMenu(new QMenu(this))
{
	verticalHeader()->setVisible(false);
	horizontalHeader()->setVisible(false);

	mPopupMenu->addAction(tr("play"),[&](){
		model()->player()->playAt(selectionModel()->currentIndex().row());
	});
	mPopupMenu->addAction(tr("copy title"),[&](){
		QApplication::clipboard()->setText(
					model()->player()->playlist()[selectionModel()->currentIndex().row()].infoTags["title"]
					);
	});
	mPopupMenu->addAction(tr("copy artist"),[&](){
		QApplication::clipboard()->setText(
					model()->player()->playlist()[selectionModel()->currentIndex().row()].infoTags["artist"]
					);
	});
	mPopupMenu->addAction(tr("copy album"),[&](){
		QApplication::clipboard()->setText(
					model()->player()->playlist()[selectionModel()->currentIndex().row()].infoTags["album"]
					);
	});
	mPopupMenu->addAction(tr("remove"),[&](){
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
	QPoint pos=mapFromParent(e->pos());
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

void PlaylistView::setModel(PlaylistModel* model)
{
	QTableView::setModel(model);
}

PlaylistModel* PlaylistView::model()
{
	return qobject_cast<PlaylistModel*>(QTableView::model());
}
