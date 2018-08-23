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
		mPlayer.play();
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
}

void MainWindow::paintEvent(QPaintEvent* e)
{
	QPainter painter(this);
	painter.setPen(QColor(0xb2,0xb2,0xb2));
	int top=height()-ui->playButton->height()-15;
	painter.drawLine(QPoint(3,top),QPoint(width()-3,top));
}

MainWindow::~MainWindow()
{
	delete ui;
}
