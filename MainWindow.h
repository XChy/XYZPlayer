#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <MusicPlayer.h>
#include <QPainter>
#include <QWidgetAction>
#include <QFileDialog>
#include <QSlider>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	explicit MainWindow(QWidget *parent = 0);
	void paintEvent(QPaintEvent* e);
	void resizeEvent(QResizeEvent* e);
	~MainWindow();

private:
	Ui::MainWindow *ui;
	MusicPlayer mPlayer;
	QSlider* mVolumeSlider;
};

#endif // MAINWINDOW_H
