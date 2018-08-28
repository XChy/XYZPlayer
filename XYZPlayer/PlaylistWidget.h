#ifndef PLAYLISTWIDGET_H
#define PLAYLISTWIDGET_H

#include <QLabel>
#include <QGraphicsEffect>
#include <XYZPlayer/MusicPlayer.h>
#include <XYZPlayer/PlaylistModel.h>
#include <XYZPlayer/PlaylistView.h>
#include <XYZPlayer/ItemDelegates.h>

namespace Ui {
class PlaylistWidget;
}

class PlaylistWidget : public QWidget
{
	Q_OBJECT

public:
	explicit PlaylistWidget(QWidget *parent = 0);

	void resizeEvent(QResizeEvent* e);

	void setPlayer(MusicPlayer* player);

private:
	PlaylistView* mView;
	PlaylistModel* mModel;
	QLabel* mTitle;

	int headerY();
};

#endif // PLAYLISTWIDGET_H
