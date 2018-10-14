#include "LyricsView.h"

LyricsView::LyricsView(QWidget* parent)
	:QListView(parent),
	  mPopupMenu(new QMenu(this))
{
	mPopupMenu->addAction(tr("Copy"),[&](){
		QApplication::clipboard()->setText(selectionModel()->selectedRows().front().data().toString());
	});
}

void LyricsView::contextMenuEvent(QContextMenuEvent* e)
{
	if(indexAt(e->pos()).isValid()){
		mPopupMenu->exec(e->globalPos());
		e->accept();
	}
}

void LyricsView::setModel(LyricsModel* model)
{
    if(this->model()){
//        disconnect(model,&LyricsModel::da)
    }
	if(model){
//		connect(model,&LyricsModel::lyricIndexChanged,[this](const QModelIndex& index){
//			scrollTo(index,PositionAtCenter);
//		});
	}
	QListView::setModel(model);
}

LyricsModel* LyricsView::model()
{
	return qobject_cast<LyricsModel*>(QListView::model());
}
