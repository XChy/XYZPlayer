#ifndef PLAYLISTWIDGET_H
#define PLAYLISTWIDGET_H

#include <QLabel>
#include <QPushButton>
#include <QFileDialog>
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
	explicit PlaylistWidget(QWidget* parent = 0);

	void resizeEvent(QResizeEvent* e);

	void setPlayer(MusicPlayer* player);

public slots:
	void on_clicked_addButton();
    void on_clicked_clearButton();
private:
	PlaylistView* mView;
	PlaylistModel* mModel;
	QLabel* mTitle;
	QPushButton* mAddButton;
    QPushButton* mClearButton;

	int headerY();
};

#endif // PLAYLISTWIDGET_H
