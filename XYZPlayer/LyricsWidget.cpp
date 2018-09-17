#include "LyricsWidget.h"

LyricsWidget::LyricsWidget(QWidget *parent)
	: QWidget(parent),
	  mModel(new LyricsModel(this)),
	  mView(new LyricsView(this)),
	  mPlayer(nullptr)
{
	mView->move(0,0);
	mView->setResizeMode(QListView::Adjust);
	mView->setItemDelegate(new LyricItemDelegate(this));
}

void LyricsWidget::resizeEvent(QResizeEvent* e)
{
	mView->setFixedSize(size());
}

MusicPlayer* LyricsWidget::player() const
{
	return mPlayer;
}

void LyricsWidget::setPlayer(MusicPlayer* player)
{
	mModel->setPlayer(player);
	mView->setModel(mModel);
	mPlayer = player;
}
