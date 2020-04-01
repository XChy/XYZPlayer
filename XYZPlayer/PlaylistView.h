#ifndef PLAYLISTVIEW_H
#define PLAYLISTVIEW_H

#include <QTableView>
#include <QHeaderView>
#include <QMenu>
#include <QApplication>
#include <QClipboard>
#include <QDesktopServices>
#include <XYZPlayer/PlaylistModel.h>

class PlaylistView : public QTableView
{
	Q_OBJECT
public:
	PlaylistView(QWidget* parent=nullptr);

	void contextMenuEvent(QContextMenuEvent *e);
	void mouseDoubleClickEvent(QMouseEvent* e);
public slots:
	void setModel(PlaylistModel* model);
	PlaylistModel* model();
private:
	QMenu* _popupMenu;
};

#endif // PLAYLISTVIEW_H
