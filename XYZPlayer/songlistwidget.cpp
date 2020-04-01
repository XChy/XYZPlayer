#include "songlistwidget.h"
#include "ui_songlistwidget.h"

SonglistWidget::SonglistWidget(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::SonglistWIdget),
	_model(new SonglistModel(this))
{
	ui->setupUi(this);
	ui->view->setModel(_model);
	ui->view->setItemDelegateForColumn(0,new TitleItemDelegate(this));
	ui->view->setItemDelegateForColumn(1,new ArtistItemDelegate(this));
	ui->view->setItemDelegateForColumn(2,new ArtistItemDelegate(this));
	ui->view->setItemDelegateForColumn(3,new DurationItemDelegate(this));
	connect(ui->return_button,&QPushButton::clicked,this,&SonglistWidget::aboutToReturn);
}

SonglistWidget::~SonglistWidget()
{
	delete ui;
}

void SonglistWidget::setSonglist(Songlist* songlist)
{
	if(songlist){
		if(songlist->isEmpty()||songlist->first().picture.isNull()){
			ui->bio_label->setPixmap(QPixmap(":/images/easy/folder.png").scaled(ui->bio_label->size()));
		}else{
			ui->bio_label->setPixmap(songlist->first().picture.scaled(ui->bio_label->size(),Qt::IgnoreAspectRatio,Qt::SmoothTransformation));
		}
		ui->songlistNameLabel->setText(songlist->name());
	}
	_model->setSonglist(songlist);
}
