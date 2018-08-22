#include "MainWindow.h"
#include "ui_MainWindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);
	ui->playButton->setProperty("is_playing",true);
	ui->volumeButton->setProperty("is_mute",false);
	ui->playbackModeButton->setProperty("playbackmode","loop");
}

void MainWindow::paintEvent(QPaintEvent* e)
{
	QPainter painter(this);
	painter.setPen(QColor(0xb2,0xb2,0xb2));
	int top=height()-ui->playButton->height()-10;
	painter.drawLine(QPoint(2,top),QPoint(width()-2,top));
}

MainWindow::~MainWindow()
{
	delete ui;
}
