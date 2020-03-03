#ifndef LYRICSVIEW_H
#define LYRICSVIEW_H

#include <QListView>
#include <QClipboard>
#include <QApplication>
#include <QContextMenuEvent>
#include <QScrollBar>
#include <QMenu>
#include <QTimer>
#include <XYZPlayer/LyricsModel.h>

class LyricsView : public QListView
{
	Q_OBJECT
public:
	LyricsView(QWidget* parent=0);

	void contextMenuEvent(QContextMenuEvent *e);
	void wheelEvent(QWheelEvent *e);
public slots:
	void setModel(LyricsModel* model);
	void onLyricsIndexChanged(const QModelIndex& index);
	LyricsModel* model();
private:
	QMenu* _popupMenu;
	bool _isWheeling;
	QTimer* _timer;
};

#endif // LYRICSVIEW_H
