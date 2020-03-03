#include "LyricsView.h"

LyricsView::LyricsView(QWidget* parent)
	:QListView(parent),
	  _popupMenu(new QMenu(this)),
	  _timer(new QTimer(this)),
	  _isWheeling(false)
{
	verticalScrollBar()->setVisible(false);
	_popupMenu->addAction(tr("Copy"),[&](){
		QApplication::clipboard()->setText(selectionModel()->selectedRows().front().data().toString());
	});
	_popupMenu->addAction(tr("Turn to"),[&](){
		model()->player()->setPosition(selectionModel()->currentIndex().data(Qt::UserRole+1).toLongLong());
	});

	_timer->setSingleShot(true);
	connect(_timer,&QTimer::timeout,[this](){
		_isWheeling=false;
	});
}

void LyricsView::contextMenuEvent(QContextMenuEvent* e)
{
	if(indexAt(e->pos()).isValid()){
		_popupMenu->exec(e->globalPos());
		e->accept();
	}
}

void LyricsView::wheelEvent(QWheelEvent* e)
{
	_timer->stop();
	_isWheeling=true;
	QListView::wheelEvent(e);
	_timer->start(3000);
}

void LyricsView::setModel(LyricsModel* model)
{
	if(this->model()){

	}
	if(model){
		connect(model,&LyricsModel::lyricIndexChanged,this,&LyricsView::onLyricsIndexChanged);
	}
	QListView::setModel(model);
}

void LyricsView::onLyricsIndexChanged(const QModelIndex& index)
{
	if(!_isWheeling){
		scrollTo(index,QListView::PositionAtCenter);
	}
}

LyricsModel* LyricsView::model()
{
	return qobject_cast<LyricsModel*>(QListView::model());
}
