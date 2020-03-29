#ifndef SONGLISTSVIEW_H
#define SONGLISTSVIEW_H

#include <QListView>
#include <QMenu>
#include <QMessageBox>
#include <XYZPlayer/SonglistsModel.h>
#include <XYZPlayer/AddSonglistDialog.h>

class SonglistsView : public QListView
{
		Q_OBJECT

	public:
		explicit SonglistsView(QWidget *parent = nullptr);

		void contextMenuEvent(QContextMenuEvent *e);
		void mouseDoubleClickEvent(QMouseEvent* e);
		QMimeData* mimeData(const QModelIndexList &indexes) const;
	signals:
		void aboutToOpenSonglist(Songlist* songlist);
	public slots:
		void setModel(SonglistsModel* model);
		SonglistsModel* model();
	private:
		QMenu* _popupMenu;
};

#endif // SONGLISTSVIEW_H
