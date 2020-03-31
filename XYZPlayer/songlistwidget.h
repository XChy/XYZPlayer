#ifndef SONGLISTWIDGET_H
#define SONGLISTWIDGET_H

#include <QWidget>

namespace Ui {
class SonglistWIdget;
}

class SonglistWidget : public QWidget
{
		Q_OBJECT

	public:
		explicit SonglistWidget(QWidget *parent = nullptr);
		~SonglistWidget();

	private:
		Ui::SonglistWIdget *ui;
};

#endif // SONGLISTWIDGET_H
