#include "songlistwidget.h"
#include "ui_songlistwidget.h"

SonglistWidget::SonglistWidget(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::SonglistWIdget)
{
	ui->setupUi(this);
}

SonglistWidget::~SonglistWidget()
{
	delete ui;
}
