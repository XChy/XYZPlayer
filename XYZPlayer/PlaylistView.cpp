#include "PlaylistView.h"

PlaylistView::PlaylistView(QWidget* parent)
	:QTableView(parent)
	,_popupMenu(new QMenu(this))
{
	setDragDropMode(QAbstractItemView::DragDrop);
	setDragEnabled(true);
	setDropIndicatorShown(true);

	verticalHeader()->setVisible(false);
	horizontalHeader()->setVisible(false);

	_popupMenu->addAction(tr("Play"),[&](){
		model()->player()->playAt(selectionModel()->currentIndex().row());
	});
	_popupMenu->addAction(tr("Open in explorer"),[&](){
		QString path=model()->player()->playlist().at(selectionModel()->currentIndex().row()).path;
		QDesktopServices::openUrl(QUrl("file:///"+
									  path.left(path.lastIndexOf("/"))
								  ));
	});
	_popupMenu->addAction(tr("Copy title"),[&](){
		QApplication::clipboard()->setText(
					model()->player()->playlist()[selectionModel()->currentIndex().row()].infoTags["title"]
				);
    });
	_popupMenu->addAction(tr("Copy artist"),[&](){
		QApplication::clipboard()->setText(
					model()->player()->playlist()[selectionModel()->currentIndex().row()].infoTags["artist"]
				);
	});
	_popupMenu->addAction(tr("Copy album"),[&](){
		QApplication::clipboard()->setText(
					model()->player()->playlist()[selectionModel()->currentIndex().row()].infoTags["album"]
				);
	});
	_popupMenu->addAction(tr("Remove"),[&](){
		int offset=0;
		for(QItemSelectionRange index:selectionModel()->selection()){
			model()->player()->removeMusics(index.top()-offset,index.bottom()+1-offset);
			offset+=index.height();
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
			_popupMenu->exec(e->globalPos());
			e->accept();
		}else{
			selectionModel()->setCurrentIndex(indexAt(pos),QItemSelectionModel::Select|QItemSelectionModel::Rows);
			_popupMenu->exec(e->globalPos());
			e->accept();
		}
	}
}

void PlaylistView::mouseDoubleClickEvent(QMouseEvent* e)
{
	QModelIndex index=indexAt(e->pos());
	if(index.isValid()&&e->button()==Qt::LeftButton){
		model()->player()->playAt(index.row());
	}
}

QMimeData* PlaylistView::mimeData(const QModelIndexList& indexes) const
{
	QMimeData* data=new QMimeData;
	QByteArray bytes;
	return data;
}

void PlaylistView::setModel(PlaylistModel* model)
{
	QTableView::setModel(model);
}

PlaylistModel* PlaylistView::model()
{
	return qobject_cast<PlaylistModel*>(QTableView::model());
}
