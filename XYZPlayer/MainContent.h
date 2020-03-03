#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPainter>
#include <QDesktopWidget>
#include <QWidgetAction>
#include <QSlider>
#include <QToolTip>
#include <QEvent>
#include <XYZPlayer/MusicPlayer.h>
#include <XYZPlayer/PlaylistWidget.h>
#include <XYZPlayer/ItemDelegates.h>

namespace Ui {
class MainWindow;
}

class MainContent : public QMainWindow
{
	Q_OBJECT

public:
	explicit MainContent(QWidget *parent = 0);
	~MainContent();

	MusicPlayer* player() const;
	QWidget* titleBar() const;

    bool eventFilter(QObject *watched, QEvent *event);
signals:
	void closeRequested();
	void minimizeRequested();
	void toggleMaximizeRequested();
public slots:
	void updateMaximumButton(Qt::WindowStates state);
	void updatePlaybackModeButton(PlaybackMode mode);

private slots:
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
	MusicPlayer* _player;
	QSlider* mVolumeSlider;
	QMenu* mVolumeMenu;

	int mReadyPos=0;
};

#endif // MAINWINDOW_H
