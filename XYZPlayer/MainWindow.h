#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPainter>
#include <QWidgetAction>
#include <QFileDialog>
#include <QSlider>
#include <QToolTip>
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
	~MainWindow();

	MusicPlayer* player() const;

	bool eventFilter(QObject *watched, QEvent *event);
private slots:
	void on_clicked_Open();
	void onCurrentIndexChanged(int oldIndex,int newIndex);
	void onInfoLoaded(int index);
	void on_clicked_playButton();
	void onVolumeSliderValueChanged(int value);
	void on_clicked_PlaybackModeButton();
	void on_clicked_VolumeButton();
	void onPosSliderPressed();
	void onPosSliderMoved(int pos);
	void onPosSliderReleased();

	void onStateChanged();

private:
	Ui::MainWindow *ui;
	MusicPlayer* mPlayer;
	QSlider* mVolumeSlider;
	QMenu* mVolumeMenu;

	int mReadyPos=0;
};

#endif // MAINWINDOW_H
