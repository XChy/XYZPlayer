#ifndef LYRICSWIDGET_H
#define LYRICSWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QFileDialog>
#include <QSettings>
#include <QPushButton>
#include <XYZPlayer/MusicPlayer.h>
#include <XYZPlayer/LyricsView.h>
#include <XYZPlayer/LyricsModel.h>
#include <XYZPlayer/ItemDelegates.h>

class LyricsWidget : public QWidget
{
		Q_OBJECT
	public:
		explicit LyricsWidget(QWidget *parent = nullptr);

		void resizeEvent(QResizeEvent* e);

		MusicPlayer* player() const;
		void setPlayer(MusicPlayer* player);

	public slots:
		void onChooseLyrics();
		void updateTipLabel();
	private:
		MusicPlayer* _player;
		QLabel* _tipLabel;
		LyricsModel* _model;
		LyricsView* _view;
		QPushButton* _chooseButton;
};

#endif // LYRICSWIDGET_H
