#ifndef SONGLISTVIEW_H
#define SONGLISTVIEW_H

#include <QTableView>
#include <QHeaderView>
#include <QMenu>
#include <XYZPlayer/SonglistModel.h>

class SonglistView : public QTableView
{
		Q_OBJECT
	public:
		SonglistView(QWidget* parent=nullptr);
		void contextMenuEvent(QContextMenuEvent *e);
		void mouseDoubleClickEvent(QMouseEvent* e);

		SonglistModel* model() const;
		void setModel(SonglistModel* model);

	private:
		QMenu* _popupMenu;
};

#endif // SONGLISTVIEW_H
