#include "LyricsWidget.h"

LyricsWidget::LyricsWidget(QWidget *parent)
	: QWidget(parent),
	  mModel(new LyricsModel(this)),
	  mView(new QListView(this)),
	  mPlayer(nullptr)
{
	mView->move(0,0);
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
	if(player){
		connect(player,&MusicPlayer::positionChanged,this,&LyricsWidget::onPositionChanged);
	}
	if(mPlayer){
		disconnect(mPlayer,&MusicPlayer::positionChanged,this,&LyricsWidget::onPositionChanged);
	}
	mModel->setPlayer(player);
	mView->setModel(mModel);
	mPlayer = player;
}

void LyricsWidget::onPositionChanged(int64_t pos)
{
	mView->update();
}
