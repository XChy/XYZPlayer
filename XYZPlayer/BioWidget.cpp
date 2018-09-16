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
		connect(player,&MusicPlayer::pictureLoaded,this,&BioWidget::onLoadedPicture);
		connect(player,&MusicPlayer::currentIndexChanged,this,&BioWidget::onCurrentIndexChanged);
	}
	if(mPlayer){
		disconnect(mPlayer,&MusicPlayer::pictureLoaded,this,&BioWidget::onLoadedPicture);
		disconnect(mPlayer,&MusicPlayer::currentIndexChanged,this,&BioWidget::onCurrentIndexChanged);
	}
	mPlayer = player;
}

void BioWidget::updatePicture()
{
	if(mPlayer->currentIndex()!=-1){
		mPictureLabel->setPixmap(QPixmap::fromImage(mPlayer->currentMusic().picture.scaled(mPictureLabel->size(),Qt::KeepAspectRatio,Qt::SmoothTransformation)));
		if(mPictureLabel->pixmap()->isNull())mPictureLabel->setText(tr("No image"));
	}else{
		mPictureLabel->setPixmap(QPixmap());
		mPictureLabel->setText(tr("No image"));
	}
}

void BioWidget::onLoadedPicture(int index)
{
	if(index==mPlayer->currentIndex()){
		updatePicture();
	}
}

void BioWidget::onCurrentIndexChanged(int oldIndex,int newIndex)
{
	if(oldIndex==newIndex)return;
	if(oldIndex!=-1){
		mPlayer->unLoadPicture(oldIndex);
	}
	if(newIndex!=-1){
		mPlayer->asyncLoadPicture(newIndex);
	}else{
		mPictureLabel->setPixmap(QPixmap());
		mPictureLabel->setText(tr("No image"));
	}
}
