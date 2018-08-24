#ifndef PLAYLISTVIEW_H
#define PLAYLISTVIEW_H

#include <QTableView>
#include <QMenu>
#include <XYZPlayer/MusicPlayer.h>

class PlaylistView : public QTableView
{
public:
	PlaylistView();
private:
	QMenu* mPopupMenu;
};

#endif // PLAYLISTVIEW_H
