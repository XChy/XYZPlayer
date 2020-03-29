#ifndef LOCALMUSICWIDGET_H
#define LOCALMUSICWIDGET_H

#include <QWidget>
#include <QMessageBox>
#include <XYZPlayer/SonglistsModel.h>
#include <XYZPlayer/SonglistsView.h>
#include <XYZPlayer/AddSonglistDialog.h>
#include <XYZPlayer/ItemDelegates.h>

namespace Ui {
class LocalMusicWidget;
}

class LocalMusicWidget : public QWidget
{
	Q_OBJECT
public:
	explicit LocalMusicWidget(QWidget *parent = nullptr);
		~LocalMusicWidget();

		Songlists& localSongs();
		Songlists localSongs() const;
		void setLocalSongs(const Songlists& localSongs);

	signals:

	private slots:
		void on_addButton_clicked();

	private:
		Ui::LocalMusicWidget *ui;
		SonglistsModel* _model;
		Songlists _local;
};

#endif // LOCALMUSICWIDGET_H
