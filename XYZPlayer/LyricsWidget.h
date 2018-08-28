#ifndef LYRICSWIDGET_H
#define LYRICSWIDGET_H

#include <QWidget>
#include <QLabel>
#include <XYZPlayer/MusicPlayer.h>
#include <QListView>
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

protected slots:
	void onPositionChanged(int64_t pos);
private:
	MusicPlayer* mPlayer;
	LyricsModel* mModel;
	QListView* mView;
};

#endif // LYRICSWIDGET_H
