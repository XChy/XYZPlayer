#include "BioWidget.h"

BioWidget::BioWidget(QWidget *parent)
	: QWidget(parent),
	  _player(nullptr),
	  _pictureLabel(new QLabel(this))
{
	_pictureLabel->move(0,0);
	_pictureLabel->setObjectName("PictureLabel");
	_pictureLabel->setAlignment(Qt::AlignCenter);
}

void BioWidget::resizeEvent(QResizeEvent* e)
{
	_pictureLabel->setFixedSize(size());
	if(_player)
		updatePicture();
}

MusicPlayer* BioWidget::player() const
{
	return _player;
}

void BioWidget::setPlayer(MusicPlayer* player)
{
	if(player){
		connect(player,&MusicPlayer::pictureLoaded,this,&BioWidget::onLoadedPicture,Qt::QueuedConnection);
		connect(player,&MusicPlayer::currentIndexChanged,this,&BioWidget::onCurrentIndexChanged);
	}
	if(_player){
		disconnect(_player,&MusicPlayer::pictureLoaded,this,&BioWidget::onLoadedPicture);
		disconnect(_player,&MusicPlayer::currentIndexChanged,this,&BioWidget::onCurrentIndexChanged);
	}
	_player = player;
}

void BioWidget::updatePicture()
{
	if(_player->currentIndex()!=-1){
		_pictureLabel->setPixmap(_player->currentMusic().picture.scaled(_pictureLabel->size(),Qt::KeepAspectRatio,Qt::SmoothTransformation));
		if(_pictureLabel->pixmap()->isNull())_pictureLabel->setText(tr("No image"));
	}else{
		_pictureLabel->setPixmap(QPixmap());
		_pictureLabel->setText(tr("No image"));
	}
}

void BioWidget::onLoadedPicture(int index)
{
	if(index==_player->currentIndex()){
		updatePicture();
	}
}

void BioWidget::onCurrentIndexChanged(int oldIndex,int newIndex)
{
	if(oldIndex==newIndex)return;
	if(oldIndex!=-1){
		_player->unLoadPicture(oldIndex);
	}
	if(newIndex!=-1){
		_player->asyncLoadPicture(newIndex);
	}else{
		_pictureLabel->setPixmap(QPixmap());
		_pictureLabel->setText(tr("No image"));
	}
}
