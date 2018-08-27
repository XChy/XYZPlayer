#ifndef PLAYLISTWIDGET_H
#define PLAYLISTWIDGET_H

#include <QLabel>
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

	void paintEvent(QPaintEvent* e);

	void setPlayer(MusicPlayer* player);

private:
	PlaylistView* mView;
	PlaylistModel* mModel;

	int headerY();
};

#endif // PLAYLISTWIDGET_H
