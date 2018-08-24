#include "MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow),
	mVolumeMenu(new QMenu(this)),
	mVolumeSlider(new QSlider),
	mPlaylistModel(new PlaylistModel(this)),
	mPlaylistView(new PlaylistView),
	mPlaylistMenu(new QMenu(this))
{
	ui->setupUi(this);
	ui->playButton->setProperty("is_playing",false);
	ui->volumeButton->setProperty("is_mute",false);
	ui->playbackModeButton->setProperty("playbackmode","loop");

	auto volumeAction=new QWidgetAction(mVolumeMenu);
	mVolumeSlider->setParent(mVolumeMenu);
	mVolumeSlider->setRange(0,100);
	mVolumeSlider->setFixedSize(25,100);
	mVolumeSlider->setValue(mPlayer.audio()->volume()*100);
	volumeAction->setDefaultWidget(mVolumeSlider);
	mVolumeMenu->setFixedSize(mVolumeSlider->size()+QSize(2,4));
	mVolumeMenu->setNoReplayFor(ui->volumeButton);
	mVolumeMenu->addActions({volumeAction});

	mPlaylistModel->setPlayer(&mPlayer);
	mPlaylistView->setModel(mPlaylistModel);
	mPlaylistView->setFixedSize(300,400);
	mPlaylistView->setParent(mPlaylistMenu);
	auto playlistAction=new QWidgetAction(mPlaylistMenu);
	playlistAction->setDefaultWidget(mPlaylistView);
	mPlaylistMenu->setFixedSize(mPlaylistView->size()+QSize(2,4));
	mPlaylistMenu->setNoReplayFor(ui->playlistButton);
	mPlaylistMenu->addActions({playlistAction});

	connect(ui->OpenAction,&QAction::triggered,this,&MainWindow::onClickedOpen);
	connect(&mPlayer,&MusicPlayer::currentIndexChanged,this,&MainWindow::onCurrentIndexChanged);
	connect(&mPlayer,&MusicPlayer::loadedInfo,this,&MainWindow::onLoadedInfo);
	connect(&mPlayer,&MusicPlayer::loadedPicture,this,&MainWindow::onLoadedPicture);
	connect(ui->playButton,&QPushButton::clicked,this,&MainWindow::onClickedPlay);
	connect(&mPlayer,&MusicPlayer::stateChanged,this,&MainWindow::onStateChanged);
	connect(ui->nextButton,&QPushButton::clicked,&mPlayer,&MusicPlayer::playNext);
	connect(ui->prevButton,&QPushButton::clicked,&mPlayer,&MusicPlayer::playPrev);
	connect(mVolumeSlider,&QSlider::valueChanged,this,&MainWindow::onVolumeSliderValueChanged);
	connect(ui->posSlider,&QSlider::sliderPressed,this,&MainWindow::onPosSliderPressed);
	connect(ui->posSlider,&QSlider::sliderMoved,&mPlayer,&MusicPlayer::setPosition);

	connect(ui->volumeButton,&QPushButton::clicked,this,&MainWindow::popupVolumeMenu);
	connect(ui->playlistButton,&QPushButton::clicked,this,&MainWindow::popupPlaylistMenu);

	connect(ui->posSlider,&QSlider::sliderReleased,this,&MainWindow::onPosSliderReleased);
	connect(ui->playbackModeButton,&QPushButton::clicked,this,&MainWindow::onClickedPlaybackMode);

	connect(&mPlayer,&MusicPlayer::durationChanged,ui->posSlider,&QSlider::setMaximum);
	connect(&mPlayer,&MusicPlayer::positionChanged,ui->posSlider,&QSlider::setValue);
}

void MainWindow::onClickedOpen()
{
	QString fileName=QFileDialog::getOpenFileName(nullptr,"Add Music",".");
	MusicObject obj;
	obj.path=fileName;
	mPlayer.addMusicToCurrent(obj);
	mPlayer.asyncLoadInfo(mPlayer.currentIndex());
	mPlayer.asyncLoadPicture(mPlayer.currentIndex());
	mPlayer.play();
}

void MainWindow::onCurrentIndexChanged()
{
	QString title=ui->titleLabel->fontMetrics().elidedText(mPlayer.currentMusic().infoTags["title"],Qt::ElideRight,ui->titleLabel->width());
	QString artist=ui->artistLabel->fontMetrics().elidedText(mPlayer.currentMusic().infoTags["artist"],Qt::ElideRight,ui->artistLabel->width());
	ui->titleLabel->setText(title);
	ui->artistLabel->setText(artist);
	ui->pictureLabel->setPixmap(QPixmap::fromImage(mPlayer.currentMusic().picture).scaled(ui->pictureLabel->size(),Qt::KeepAspectRatio,Qt::SmoothTransformation));
	ui->posSlider->setRange(0,0);
	ui->posSlider->setValue(0);
}

void MainWindow::onLoadedInfo(int index)
{
	if(index==mPlayer.currentIndex()){
		QString title=ui->titleLabel->fontMetrics().elidedText(mPlayer.currentMusic().infoTags["title"],Qt::ElideRight,ui->titleLabel->width());
		QString artist=ui->artistLabel->fontMetrics().elidedText(mPlayer.currentMusic().infoTags["artist"],Qt::ElideRight,ui->artistLabel->width());
		ui->titleLabel->setText(title);
		ui->artistLabel->setText(artist);
	}
}

void MainWindow::onLoadedPicture(int index)
{
	if(index==mPlayer.currentIndex()){
		ui->pictureLabel->setPixmap(QPixmap::fromImage(mPlayer.currentMusic().picture).scaled(ui->pictureLabel->size(),Qt::KeepAspectRatio,Qt::SmoothTransformation));
	}
}

void MainWindow::onClickedPlay()
{
	if(mPlayer.isPlaying()){
		mPlayer.pause(!mPlayer.isPaused());
	}else{
		mPlayer.play();
	}
	ui->playButton->setProperty("is_playing",!mPlayer.isPaused()&&mPlayer.isPlaying());
	ui->playButton->style()->unpolish(ui->playButton);
	ui->playButton->style()->polish(ui->playButton);
	ui->playButton->update();
}

void MainWindow::onVolumeSliderValueChanged(int value)
{
	mPlayer.audio()->setVolume(qreal(value)/100);
}

void MainWindow::onClickedPlaybackMode()
{
	mPlayer.setPlaybackMode(mPlayer.playbackMode() != Random ? PlaybackMode(mPlayer.playbackMode()+1) : Loop);
	switch (mPlayer.playbackMode()) {
		case Loop:
			ui->playbackModeButton->setProperty("playbackmode","loop");
			break;
		case CurrentItemLoop:
			ui->playbackModeButton->setProperty("playbackmode","current_loop");
			break;
		case Sequential:
			ui->playbackModeButton->setProperty("playbackmode","sequential");
			break;
		case Random:
			ui->playbackModeButton->setProperty("playbackmode","random");
			break;
	}
	ui->playbackModeButton->style()->unpolish(ui->playbackModeButton);
	ui->playbackModeButton->style()->polish(ui->playbackModeButton);
	ui->playbackModeButton->update();
}

void MainWindow::popupVolumeMenu()
{
	QPoint btnPos=ui->volumeButton->pos();
	QPoint globalPos=this->mapToGlobal(QPoint(btnPos.x(),footerY()-mVolumeMenu->height()-3));
	mVolumeMenu->move(globalPos);
	mVolumeMenu->show();
}

void MainWindow::popupPlaylistMenu()
{
	QPoint globalPos=this->mapToGlobal(QPoint(width()-mPlaylistMenu->width()-3,footerY()-mPlaylistMenu->height()-3));
	mPlaylistMenu->move(globalPos);
	mPlaylistMenu->show();
}

void MainWindow::onPosSliderPressed()
{
	mPlayer.audio()->close();
	mPlayer.audio()->clear();
}

void MainWindow::onStateChanged()
{
	ui->playButton->setProperty("is_playing",(!mPlayer.isPaused()&&mPlayer.isPlaying())||mPlayer.canPlayback());
	ui->playButton->style()->unpolish(ui->playButton);
	ui->playButton->style()->polish(ui->playButton);
	ui->playButton->update();
}

void MainWindow::onPosSliderReleased()
{
	if(mPlayer.currentIndex()!=-1)
		mPlayer.audio()->open();
}

int MainWindow::footerY()
{
	return height()-ui->playButton->height()-15;
}

void MainWindow::paintEvent(QPaintEvent* e)
{
	QPainter painter(this);
	painter.setPen(QColor(0xb2,0xb2,0xb2));
	int y = footerY();
	painter.drawLine(QPoint(3,y),QPoint(width()-3,y));
}

void MainWindow::resizeEvent(QResizeEvent* e)
{
	if(!mPlayer.playlist().isEmpty())
		ui->pictureLabel->setPixmap(QPixmap::fromImage(mPlayer.currentMusic().picture).scaled(ui->pictureLabel->size(),Qt::KeepAspectRatio,Qt::SmoothTransformation));
}

MainWindow::~MainWindow()
{
	delete ui;
}
