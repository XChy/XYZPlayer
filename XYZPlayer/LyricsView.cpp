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
