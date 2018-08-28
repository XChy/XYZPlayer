#include "BioWidget.h"

BioWidget::BioWidget(QWidget *parent)
	: QWidget(parent),
	  mPlayer(nullptr),
	  mPictureLabel(new QLabel(this))
{
	mPictureLabel->move(0,0);
	mPictureLabel->setAlignment(Qt::AlignCenter);
}

void BioWidget::resizeEvent(QResizeEvent* e)
{
	mPictureLabel->setFixedSize(size());
	if(mPlayer)
		updatePicture();
}

MusicPlayer* BioWidget::player() const
{
	return mPlayer;
}

void BioWidget::setPlayer(MusicPlayer* player)
{
	if(player){
		connect(player,&MusicPlayer::loadedPicture,this,&BioWidget::onLoadedPicture);
		connect(player,&MusicPlayer::currentIndexChanged,this,&BioWidget::onCurrentIndexChanged);
	}
	if(mPlayer){
		disconnect(mPlayer,&MusicPlayer::loadedPicture,this,&BioWidget::onLoadedPicture);
		disconnect(mPlayer,&MusicPlayer::currentIndexChanged,this,&BioWidget::onCurrentIndexChanged);
	}
	mPlayer = player;
}

void BioWidget::updatePicture()
{
	if(mPlayer->currentIndex()!=-1)
		mPictureLabel->setPixmap(QPixmap::fromImage(mPlayer->currentMusic().d->picture.scaled(mPictureLabel->size(),Qt::KeepAspectRatio,Qt::SmoothTransformation)));
}

void BioWidget::onLoadedPicture(int index)
{
	if(index==mPlayer->currentIndex()){
		updatePicture();
	}
}

void BioWidget::onCurrentIndexChanged(int index)
{
	if(index==-1){
		mPictureLabel->setPixmap(QPixmap());
	}else{
		updatePicture();
	}
}
