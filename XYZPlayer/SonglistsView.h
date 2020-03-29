#ifndef SONGLISTSVIEW_H
#define SONGLISTSVIEW_H

#include <QListView>
#include <QMenu>
#include <XYZPlayer/SonglistsModel.h>

class SonglistsView : public QListView
{
		Q_OBJECT

	public:
		explicit SonglistsView(QWidget *parent = nullptr);

		void contextMenuEvent(QContextMenuEvent *e);
		void mouseDoubleClickEvent(QMouseEvent* e);
		QMimeData* mimeData(const QModelIndexList &indexes) const;
	public slots:
		void setModel(SonglistsModel* model);
		SonglistsModel* model();
	private:
		QMenu* _popupMenu;
};

#endif // SONGLISTSVIEW_H
