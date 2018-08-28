#include "PlaylistWidget.h"
#include <QDebug>

PlaylistWidget::PlaylistWidget(QWidget *parent) :
	QWidget(parent),
	mView(new PlaylistView(this)),
	mTitle(new QLabel(tr("Playlist"),this)),
	mModel(new PlaylistModel(this))
{
	mTitle->setObjectName("PlaylistTitle");
	mTitle->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
	mTitle->move(0,0);
}

void PlaylistWidget::resizeEvent(QResizeEvent* e)
{
	mTitle->setFixedSize(width(),headerY());
	mView->move(0,headerY());
	mView->setFixedSize(width(),height()-headerY());
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

int PlaylistWidget::headerY()
{
	return 25;
}
