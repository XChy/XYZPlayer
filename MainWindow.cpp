#include "MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow),
	mVolumeSlider(new QSlider)
{
	ui->setupUi(this);
	ui->playButton->setProperty("is_playing",false);
	ui->volumeButton->setProperty("is_mute",false);
	ui->playbackModeButton->setProperty("playbackmode","loop");
	auto volumeMenu=new QMenu(ui->volumeButton);
	auto volumeAction=new QWidgetAction(volumeMenu);
	mVolumeSlider->setRange(0,100);
	mVolumeSlider->setFixedSize(25,100);
	volumeAction->setDefaultWidget(mVolumeSlider);
	volumeMenu->addActions({volumeAction});
	ui->volumeButton->setMenu(volumeMenu);

	connect(ui->OpenAction,&QAction::triggered,[&](){
		QString fileName=QFileDialog::getOpenFileName(nullptr,"Add Music",".");
		MusicObject obj;
		obj.path=fileName;
		mPlayer.addMusicToCurrent(obj);
		mPlayer.loadInfo(mPlayer.currentIndex());
		mPlayer.loadPicture(mPlayer.currentIndex());
		mPlayer.play();
	});

	connect(&mPlayer,&MusicPlayer::currentIndexChanged,[&](){
		QString title=ui->titleLabel->fontMetrics().elidedText(mPlayer.currentMusic().info["title"],Qt::ElideRight,ui->titleLabel->width());
		QString artist=ui->artistLabel->fontMetrics().elidedText(mPlayer.currentMusic().info["artist"],Qt::ElideRight,ui->artistLabel->width());
		ui->titleLabel->setText(title);
		ui->artistLabel->setText(artist);
		ui->pictureLabel->setPixmap(QPixmap::fromImage(mPlayer.currentMusic().picture).scaled(ui->pictureLabel->size(),Qt::KeepAspectRatio,Qt::SmoothTransformation));
	});

	connect(&mPlayer,&MusicPlayer::loadedInfo,[&](int index){
		if(index==mPlayer.currentIndex()){
			QString title=ui->titleLabel->fontMetrics().elidedText(mPlayer.currentMusic().info["title"],Qt::ElideRight,ui->titleLabel->width());
			QString artist=ui->artistLabel->fontMetrics().elidedText(mPlayer.currentMusic().info["artist"],Qt::ElideRight,ui->artistLabel->width());
			ui->titleLabel->setText(title);
			ui->artistLabel->setText(artist);
		}
	});

	connect(&mPlayer,&MusicPlayer::loadedPicture,[&](int index){
		if(index==mPlayer.currentIndex()){
			ui->pictureLabel->setPixmap(QPixmap::fromImage(mPlayer.currentMusic().picture).scaled(ui->pictureLabel->size(),Qt::KeepAspectRatio,Qt::SmoothTransformation));
		}
	});

	connect(ui->playButton,&QPushButton::clicked,[&](){
		if(mPlayer.isPlaying()){
			mPlayer.pause(!mPlayer.isPaused());
		}else{
			mPlayer.play();
		}
		ui->playButton->setProperty("is_playing",!mPlayer.isPaused()&&mPlayer.isPlaying());
		ui->playButton->style()->unpolish(ui->playButton);
		ui->playButton->style()->polish(ui->playButton);
		ui->playButton->update();
	});

	connect(&mPlayer,&MusicPlayer::stateChanged,[&](){
		ui->playButton->setProperty("is_playing",(!mPlayer.isPaused()&&mPlayer.isPlaying())||mPlayer.canPlayback());
		ui->playButton->style()->unpolish(ui->playButton);
		ui->playButton->style()->polish(ui->playButton);
		ui->playButton->update();
	});

	connect(ui->nextButton,&QPushButton::clicked,[&](){
		mPlayer.playNext();
	});
	connect(ui->prevButton,&QPushButton::clicked,[&](){
		mPlayer.playPrev();
	});

	connect(mVolumeSlider,&QSlider::valueChanged,[&](int value){
		mPlayer.audio()->setVolume(qreal(value)/100);
	});

	connect(ui->posSlider,&QSlider::sliderPressed,[&](){
		mPlayer.audio()->close();
		mPlayer.audio()->clear();
	});

	connect(ui->posSlider,&QSlider::sliderMoved,[&](int value){
		mPlayer.setPosition(value);
	});

	connect(ui->posSlider,&QSlider::sliderReleased,[&](){
		if(mPlayer.currentIndex()!=-1)
			mPlayer.audio()->open();
	});
	connect(ui->playbackModeButton,&QPushButton::clicked,[&](){
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
	});

	connect(&mPlayer,&MusicPlayer::durationChanged,[&](qint64 duration){
		ui->posSlider->setRange(0,duration);
	});

	connect(&mPlayer,&MusicPlayer::positionChanged,[&](qint64 pos){
		ui->posSlider->setValue(pos);
	});
}

void MainWindow::paintEvent(QPaintEvent* e)
{
	QPainter painter(this);
	painter.setPen(QColor(0xb2,0xb2,0xb2));
	int top=height()-ui->playButton->height()-15;
	painter.drawLine(QPoint(3,top),QPoint(width()-3,top));
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
