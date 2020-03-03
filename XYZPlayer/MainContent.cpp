#include "MainContent.h"
#include "ui_MainWindow.h"

MainContent::MainContent(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow),
	mPlayer(new MusicPlayer(QApplication::desktop())),
	mVolumeMenu(new QMenu(this)),
	mVolumeSlider(new QSlider)
{
	setAcceptDrops(true);

	ui->setupUi(this);

	ui->center->setSizes({300,width()-300});
	ui->bioPage->setPlayer(mPlayer);
	ui->lyricsPage->setPlayer(mPlayer);
	ui->contentWidget->setCurrentWidget(ui->bioPage);

	ui->bioLabel->setProperty("is_current",true);
	ui->playButton->setProperty("is_playing",false);
	ui->volumeButton->setProperty("is_mute",false);

	auto volumeAction=new QWidgetAction(mVolumeMenu);
	mVolumeSlider->setParent(mVolumeMenu);
	mVolumeSlider->setRange(0,100);
	mVolumeSlider->setFixedSize(25,100);
	volumeAction->setDefaultWidget(mVolumeSlider);
	mVolumeMenu->setFixedSize(mVolumeSlider->size()+QSize(2,4));
	mVolumeMenu->setNoReplayFor(ui->volumeButton);
	mVolumeMenu->addActions({volumeAction});

	ui->playlistWidget->setPlayer(mPlayer);

	connect(mPlayer,&MusicPlayer::currentIndexChanged,this,&MainContent::onCurrentIndexChanged);
	connect(mPlayer,&MusicPlayer::infoLoaded,this,&MainContent::onInfoLoaded,Qt::QueuedConnection);
	connect(ui->playButton,&QPushButton::clicked,this,&MainContent::on_clicked_playButton);
	connect(mPlayer,&MusicPlayer::stateChanged,this,&MainContent::onStateChanged);
	connect(ui->nextButton,&QPushButton::clicked,mPlayer,&MusicPlayer::playNext);
	connect(ui->prevButton,&QPushButton::clicked,mPlayer,&MusicPlayer::playPrev);
	connect(mVolumeSlider,&QSlider::valueChanged,this,&MainContent::onVolumeSliderValueChanged);
	connect(ui->posSlider,&QSlider::sliderPressed,this,&MainContent::onPosSliderPressed);
	connect(ui->posSlider,&QSlider::sliderMoved,this,&MainContent::onPosSliderMoved);

	connect(ui->minButton,&QPushButton::clicked,this,&MainContent::minimizeRequested);
	connect(ui->maxButton,&QPushButton::clicked,this,&MainContent::toggleMaximizeRequested);
	connect(ui->closeButton,&QPushButton::clicked,this,&MainContent::closeRequested);

	ui->logoLabel->setPixmap(QIcon("./res/images/logo.ico").pixmap(ui->logoLabel->size()));

	ui->musicsLabel->installEventFilter(this);
	ui->bioLabel->installEventFilter(this);
	ui->lyricsLabel->installEventFilter(this);

	connect(ui->volumeButton,&QPushButton::clicked,this,&MainContent::on_clicked_VolumeButton);

	connect(ui->posSlider,&QSlider::sliderReleased,this,&MainContent::onPosSliderReleased);

	connect(ui->playbackModeButton,&QPushButton::clicked,this,&MainContent::on_clicked_PlaybackModeButton);
	connect(mPlayer,&MusicPlayer::playbackModeChanged,this,&MainContent::updatePlaybackModeButton);

	connect(mPlayer,&MusicPlayer::durationChanged,ui->posSlider,&QSlider::setMaximum);
	connect(mPlayer,&MusicPlayer::positionChanged,ui->posSlider,&QSlider::setValue);

	MusicUtil::loadPlaylist(mPlayer);
	MusicUtil::loadPlayerSetting(mPlayer);
	mVolumeSlider->setValue(mPlayer->audio()->volume()*100);
}

void MainContent::onCurrentIndexChanged(int oldIndex, int newIndex)
{
	if(newIndex==-1){
		ui->titleLabel->setText(QString());
		ui->artistLabel->setText(QString());
		ui->titleLabel->setFixedHeight(0);
		ui->artistLabel->setFixedHeight(0);
	}else{
		QString title=ui->titleLabel->fontMetrics().elidedText(mPlayer->currentMusic().infoTags["title"],Qt::ElideRight,ui->titleLabel->width());
		QString artist=ui->artistLabel->fontMetrics().elidedText(mPlayer->currentMusic().infoTags["artist"],Qt::ElideRight,ui->artistLabel->width());
		ui->titleLabel->setText(title);
		ui->artistLabel->setText(artist);
		ui->titleLabel->setFixedHeight(ui->titleLabel->sizeHint().height());
		ui->artistLabel->setFixedHeight(ui->artistLabel->sizeHint().height());
	}

	ui->posSlider->setRange(0,0);
	ui->posSlider->setValue(0);
}

void MainContent::onInfoLoaded(int index)
{
	if(index==mPlayer->currentIndex()){
		QString title=ui->titleLabel->fontMetrics().elidedText(mPlayer->currentMusic().infoTags["title"],Qt::ElideRight,ui->titleLabel->width());
		QString artist=ui->artistLabel->fontMetrics().elidedText(mPlayer->currentMusic().infoTags["artist"],Qt::ElideRight,ui->artistLabel->width());
		ui->titleLabel->setFixedHeight(ui->titleLabel->sizeHint().height());
		ui->artistLabel->setFixedHeight(ui->artistLabel->sizeHint().height());
		ui->titleLabel->setText(title);
		ui->artistLabel->setText(artist);
	}
}

void MainContent::on_clicked_playButton()
{
	if(mPlayer->isPlaying()){
		mPlayer->pause(!mPlayer->isPaused());
	}else{
		mPlayer->play();
	}
	ui->playButton->setProperty("is_playing",!mPlayer->isPaused()&&mPlayer->isPlaying());
	ui->playButton->style()->unpolish(ui->playButton);
	ui->playButton->style()->polish(ui->playButton);
	ui->playButton->update();
}
void MainContent::onVolumeSliderValueChanged(int value)
{
	mPlayer->audio()->setVolume(qreal(value)/100);
}

void MainContent::updatePlaybackModeButton(PlaybackMode mode)
{
	switch (mode) {
	case Loop:
		ui->playbackModeButton->setProperty("playbackmode","loop");
		QToolTip::showText(mapToGlobal(QPoint(ui->playbackModeButton->x(),ui->footerWidget->y()-30)),tr("List loop"),this,rect(),5000);
		break;
	case CurrentItemLoop:
		ui->playbackModeButton->setProperty("playbackmode","current_loop");
		QToolTip::showText(mapToGlobal(QPoint(ui->playbackModeButton->x(),ui->footerWidget->y()-30)),tr("Single loop"),this,rect(),5000);
		break;
	case Sequential:
		ui->playbackModeButton->setProperty("playbackmode","sequential");
		QToolTip::showText(mapToGlobal(QPoint(ui->playbackModeButton->x(),ui->footerWidget->y()-30)),tr("Sequentially"),this,rect(),5000);
		break;
	case Random:
		ui->playbackModeButton->setProperty("playbackmode","random");
		QToolTip::showText(mapToGlobal(QPoint(ui->playbackModeButton->x(),ui->footerWidget->y()-30)),tr("Random"),this,rect(),5000);
		break;
	}
	style()->unpolish(ui->playbackModeButton);
	style()->polish(ui->playbackModeButton);
	ui->playbackModeButton->update();
}

void MainContent::on_clicked_PlaybackModeButton()
{
	mPlayer->setPlaybackMode(mPlayer->playbackMode() != Random ? PlaybackMode(mPlayer->playbackMode()+1) : Loop);
}

void MainContent::on_clicked_VolumeButton()
{
	QPoint btnPos=ui->volumeButton->pos();
	QPoint globalPos=this->mapToGlobal(QPoint(btnPos.x(),ui->footerWidget->y()-mVolumeMenu->height()-3));
	mVolumeMenu->move(globalPos);
	mVolumeMenu->show();
}

void MainContent::onPosSliderPressed()
{
	mPlayer->audio()->close();
	mPlayer->audio()->clear();
}

void MainContent::onPosSliderMoved(int pos)
{
	mPlayer->setPosition(pos);
}

void MainContent::onPosSliderReleased()
{
	if(mPlayer->currentIndex()!=-1){
		mPlayer->audio()->open();
	}
}

void MainContent::onStateChanged()
{
	ui->playButton->setProperty("is_playing",(!mPlayer->isPaused()&&mPlayer->isPlaying())||mPlayer->canPlayback());
	style()->unpolish(ui->playButton);
	style()->polish(ui->playButton);
	ui->playButton->update();
}

MusicPlayer* MainContent::player() const
{
	return mPlayer;
}

QWidget*MainContent::titleBar() const
{
	return ui->titleBar;
}

bool MainContent::eventFilter(QObject* watched, QEvent* event)
{
	if(event->type()==QEvent::MouseButtonPress){
		if(watched==ui->musicsLabel){
			ui->contentWidget->setCurrentWidget(ui->musicsPage);
			ui->musicsLabel->setProperty("is_current",true);
			ui->bioLabel->setProperty("is_current",false);
			ui->lyricsLabel->setProperty("is_current",false);
		}else if(watched==ui->bioLabel){
			ui->contentWidget->setCurrentWidget(ui->bioPage);
			ui->musicsLabel->setProperty("is_current",false);
			ui->bioLabel->setProperty("is_current",true);
			ui->lyricsLabel->setProperty("is_current",false);
		}else if(watched==ui->lyricsLabel){
			ui->contentWidget->setCurrentWidget(ui->lyricsPage);
			ui->musicsLabel->setProperty("is_current",false);
			ui->bioLabel->setProperty("is_current",false);
			ui->lyricsLabel->setProperty("is_current",true);
		}else{
			return QMainWindow::eventFilter(watched,event);
		}
		style()->unpolish(ui->musicsLabel);
		style()->polish(ui->musicsLabel);
		style()->unpolish(ui->bioLabel);
		style()->polish(ui->bioLabel);
		style()->unpolish(ui->lyricsLabel);
		style()->polish(ui->lyricsLabel);
		ui->musicsLabel->update();
		ui->bioLabel->update();
		ui->lyricsLabel->update();
		return true;
	}
	return QMainWindow::eventFilter(watched,event);
}

void MainContent::updateMaximumButton(Qt::WindowStates state)
{
	ui->maxButton->setProperty("isMaximized",state==Qt::WindowMaximized);
	QApplication::style()->unpolish(ui->maxButton);
	QApplication::style()->polish(ui->maxButton);
}

MainContent::~MainContent()
{
	MusicUtil::savePlaylist(mPlayer);
	MusicUtil::savePlayerSetting(mPlayer);
	delete ui;
}
