#include "PlaylistWidget.h"
#include "ui_PlaylistWidget.h"
#include <QDebug>

PlaylistWidget::PlaylistWidget(QWidget *parent) :
	QWidget(parent),
	mView(new PlaylistView(this)),
	mModel(new PlaylistModel(this))
{
	QLabel* title=new QLabel(tr("Playlist"),this);
	title->move(0,0);
	title->setFixedSize(300,25);
	mView->move(0,25);
	mView->setFixedSize(300,375);
	setFixedSize(300,400);
}

void PlaylistWidget::setPlayer(MusicPlayer* player)
{
	mModel->setPlayer(player);
	mView->setModel(mModel);
	mView->setItemDelegateForColumn(0,new PlayingItemDelegate(this));
	mView->setItemDelegateForColumn(1,new TitleItemDelegate(this));
	mView->setItemDelegateForColumn(2,new ArtistItemDelegate(this));
	mView->setItemDelegateForColumn(3,new DurationItemDelegate(this));
	mView->setColumnWidth(0,30);
	mView->setColumnWidth(3,40);
	mView->horizontalHeader()->setSectionResizeMode(0,QHeaderView::Fixed);
	mView->horizontalHeader()->setSectionResizeMode(1,QHeaderView::Stretch);
	mView->horizontalHeader()->setSectionResizeMode(2,QHeaderView::ResizeToContents);
	mView->horizontalHeader()->setSectionResizeMode(3,QHeaderView::Fixed);
}
