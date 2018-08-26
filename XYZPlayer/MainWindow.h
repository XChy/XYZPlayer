#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPainter>
#include <QWidgetAction>
#include <QFileDialog>
#include <QSlider>
#include <XYZPlayer/MusicPlayer.h>
#include <XYZPlayer/PlaylistWidget.h>
#include <XYZPlayer/ItemDelegates.h>

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

private slots:
	void onClickedOpen();
	void onCurrentIndexChanged(int index);
	void onLoadedInfo(int index);
	void onLoadedPicture(int index);
	void onClickedPlay();
	void onVolumeSliderValueChanged(int value);
	void onClickedPlaybackMode();
	void popupVolumeMenu();
	void popupPlaylistMenu();
	void onPosSliderPressed();
	void onStateChanged();
	void onPosSliderReleased();

private:
	Ui::MainWindow *ui;
	MusicPlayer* mPlayer;
	QSlider* mVolumeSlider;
	QMenu* mVolumeMenu;

	PlaylistWidget* mPlaylistWidget;
	QMenu* mPlaylistMenu;

	int footerY();
};

#endif // MAINWINDOW_H
