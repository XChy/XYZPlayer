#ifndef SONGLISTWIDGET_H
#define SONGLISTWIDGET_H

#include <QWidget>
#include <XYZPlayer/SonglistModel.h>
#include <XYZPlayer/ItemDelegates.h>

namespace Ui {
class SonglistWIdget;
}

class SonglistWidget : public QWidget
{
		Q_OBJECT

	public:
		explicit SonglistWidget(QWidget *parent = nullptr);
		~SonglistWidget();

	public slots:
		void setSonglist(Songlist* songlist);
	signals:
		void aboutToReturn();
	private:
		Ui::SonglistWIdget *ui;
		SonglistModel* _model;
};

#endif // SONGLISTWIDGET_H
