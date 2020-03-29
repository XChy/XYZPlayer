#include "SonglistsView.h"

SonglistsView::SonglistsView(QWidget *parent) :
	QListView(parent),
	_popupMenu(new QMenu(this))
{
	setViewMode(IconMode);
	setIconSize(QSize(90,90));
	setGridSize(QSize(110,110));
	setUniformItemSizes(true);

	setResizeMode(Adjust);

	setDragDropMode(QAbstractItemView::DragDrop);
	setDragEnabled(true);
	setDropIndicatorShown(true);

	_popupMenu->addAction(tr("Edit"),[this](){
		QModelIndex index=currentIndex();
		AddSonglistDialog dialog;
		dialog.setSonglistName(index.data().toString());
		if(dialog.exec()){
			QString name=dialog.songlistName();
			if(name==index.data().toString()){
				return;
			}
			if(name.isEmpty()){
				QMessageBox::warning(this,tr("Empty name!"),tr("Empty name is illegal"));
				return;
			}
			for(Songlist& list:(*model()->songlists())){
				if(list.name()==name){
					QMessageBox::warning(this,tr("Duplication of name!"),tr("This name of songlist is duplicated"));
					return;
				}
			}
			model()->songlists()->operator[](index.row()).setName(name);
		}
		model()->refresh();
	});
	_popupMenu->addAction(tr("Remove"),[this](){
		QModelIndex index=currentIndex();
		if(QMessageBox::question(this,tr("Remove"),tr("Do you really want to remove this songlist?"))==QMessageBox::Yes){
			model()->songlists()->removeAt(index.row());
			model()->refresh();
		}
	});
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
	QPoint pos=e->pos();
	QModelIndex index=indexAt(pos);
	if(index.isValid()){
		emit aboutToOpenSonglist(&(model()->songlists()->operator[](index.row())));
	}
}

QMimeData* SonglistsView::mimeData(const QModelIndexList& indexes) const
{
	QMimeData* data=new QMimeData;
	QByteArray bytes;
	return data;
}

void SonglistsView::setModel(SonglistsModel* model)
{
	QListView::setModel(model);
}

SonglistsModel* SonglistsView::model()
{
	return (SonglistsModel*)QListView::model();
}
