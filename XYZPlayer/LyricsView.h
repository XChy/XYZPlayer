#ifndef LYRICSVIEW_H
#define LYRICSVIEW_H

#include <QListView>
#include <QClipboard>
#include <QApplication>
#include <QContextMenuEvent>
#include <QMenu>
#include <XYZPlayer/LyricsModel.h>

class LyricsView : public QListView
{
	Q_OBJECT
public:
	LyricsView(QWidget* parent=0);

	void contextMenuEvent(QContextMenuEvent *e);
public slots:
	void setModel(LyricsModel* model);
	LyricsModel* model();
private:
	QMenu* mPopupMenu;
};

#endif // LYRICSVIEW_H
