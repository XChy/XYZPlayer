#ifndef PLAYLISTVIEW_H
#define PLAYLISTVIEW_H

#include <QTableView>
#include <QHeaderView>
#include <QMenu>
#include <QApplication>
#include <QClipboard>
#include <XYZPlayer/PlaylistModel.h>

class PlaylistView : public QTableView
{
	Q_OBJECT
public:
	PlaylistView(QWidget* parent=nullptr);

	void contextMenuEvent(QContextMenuEvent *e);
public slots:
	void setModel(PlaylistModel* model);
	PlaylistModel* model();
private:
	QMenu* mPopupMenu;
};

#endif // PLAYLISTVIEW_H
