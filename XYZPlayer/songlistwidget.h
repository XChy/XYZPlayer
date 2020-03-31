#ifndef SONGLISTWIDGET_H
#define SONGLISTWIDGET_H

#include <QWidget>

namespace Ui {
class SonglistWIdget;
}

class SonglistWIdget : public QWidget
{
		Q_OBJECT

	public:
		explicit SonglistWIdget(QWidget *parent = nullptr);
		~SonglistWIdget();

	private:
		Ui::SonglistWIdget *ui;
};

#endif // SONGLISTWIDGET_H
