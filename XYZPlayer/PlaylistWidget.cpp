#include "PlaylistWidget.h"
#include <QDebug>

PlaylistWidget::PlaylistWidget(QWidget *parent) :
	QWidget(parent),
	mView(new PlaylistView(this)),
	mTitle(new QLabel(tr("Playlist"),this)),
	mModel(new PlaylistModel(this)),
    mAddButton(new QPushButton(this)),
    mClearButton(new QPushButton(this))
{
	mTitle->setObjectName("PlaylistTitle");
	mTitle->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
	mTitle->move(0,0);
	mAddButton->setObjectName("AddButton");
	mAddButton->setCursor(Qt::PointingHandCursor);
	mAddButton->setFixedSize(30,30);
    mClearButton->setObjectName("ClearButton");
    mClearButton->setCursor(Qt::PointingHandCursor);
    mClearButton->setFixedSize(30,30);
	connect(mAddButton,&QPushButton::clicked,this,&PlaylistWidget::on_clicked_addButton);
    connect(mClearButton,&QPushButton::clicked,this,&PlaylistWidget::on_clicked_clearButton);
}

void PlaylistWidget::resizeEvent(QResizeEvent* e)
{
	mTitle->setFixedSize(width(),headerY());
	mView->move(0,headerY());
	mView->setFixedSize(width(),height()-headerY());
    mAddButton->move(width()-mAddButton->width(),0);
    mClearButton->move(mAddButton->x()-mClearButton->width()-5,0);
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

void PlaylistWidget::on_clicked_addButton()
{
    QSettings setting("../data/settings.ini",QSettings::IniFormat);
    QFileDialog dialog(this,tr("Add Musics"),setting.value("PlaylistFileDialog/open_dir",QString()).toString());
	dialog.setAcceptMode(QFileDialog::AcceptOpen);
	dialog.setFileMode(QFileDialog::ExistingFiles);
    dialog.setNameFilters({
                              tr("Music Files (*.mp3 *.ogg *.flac *.wav *.wma)"),
                              tr("All Files (*)")
                          });
	if(dialog.exec())
	{
		auto fileNames = dialog.selectedFiles();
		int beginIndex=mModel->player()->playlist().size();
		if(fileNames.isEmpty()){
			return;
		}else{
			setting.beginGroup("PlaylistFileDialog");
			setting.setValue("open_dir",dialog.directory().path());
			setting.endGroup( );
		}
		for(QString fileName:fileNames){
			MusicObject obj;
			obj.path=fileName;
			obj.lyrics.path=fileName.left(fileName.lastIndexOf('.')).append(".lrc");
			mModel->player()->addMusic(obj);
		}
		mModel->player()->asyncLoadInfo(beginIndex,mModel->player()->playlist().size());
		mModel->player()->playAt(beginIndex);
	}

}

void PlaylistWidget::on_clicked_clearButton()
{
    mModel->player()->clearAllMusic();
}

int PlaylistWidget::headerY()
{
	return 30;
}
