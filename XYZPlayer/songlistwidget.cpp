#include "songlistwidget.h"
#include "ui_songlistwidget.h"

SonglistWIdget::SonglistWIdget(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::SonglistWIdget)
{
	ui->setupUi(this);
}

SonglistWIdget::~SonglistWIdget()
{
	delete ui;
}
