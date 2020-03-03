#include "PlaylistWidget.h"
#include <QDebug>

PlaylistWidget::PlaylistWidget(QWidget *parent) :
	QWidget(parent),
	_view(new PlaylistView(this)),
	_title(new QLabel(tr("Playlist"),this)),
	_model(new PlaylistModel(this)),
	_addButton(new QPushButton(this)),
	_clearButton(new QPushButton(this))

{
	_title->setObjectName("PlaylistTitle");
	_title->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
	_title->move(0,0);
	_addButton->setObjectName("AddButton");
	_addButton->setCursor(Qt::PointingHandCursor);
	_addButton->setFixedSize(30,30);
	_clearButton->setObjectName("ClearButton");
	_clearButton->setCursor(Qt::PointingHandCursor);
	_clearButton->setFixedSize(30,30);
	connect(_addButton,&QPushButton::clicked,this,&PlaylistWidget::on_clicked_addButton);
	connect(_clearButton,&QPushButton::clicked,this,&PlaylistWidget::on_clicked_clearButton);
}

void PlaylistWidget::resizeEvent(QResizeEvent* e)
{
	_title->setFixedSize(width(),headerY());
	_view->move(0,headerY());
	_view->setFixedSize(width(),height()-headerY());
	_addButton->move(width()-_addButton->width(),0);
	_clearButton->move(_addButton->x()-_clearButton->width()-5,0);
}

void PlaylistWidget::setPlayer(MusicPlayer* player)
{
	_model->setPlayer(player);
	_view->setModel(_model);
	_view->setItemDelegateForColumn(0,new PlayingItemDelegate(this));
	_view->setItemDelegateForColumn(1,new TitleItemDelegate(this));
	_view->setItemDelegateForColumn(2,new ArtistItemDelegate(this));
	_view->setItemDelegateForColumn(3,new DurationItemDelegate(this));
	_view->setColumnWidth(0,30);
	_view->setColumnWidth(3,40);
	_view->horizontalHeader()->setSectionResizeMode(0,QHeaderView::Fixed);
	_view->horizontalHeader()->setSectionResizeMode(1,QHeaderView::Stretch);
	_view->horizontalHeader()->setSectionResizeMode(2,QHeaderView::ResizeToContents);
	_view->horizontalHeader()->setSectionResizeMode(3,QHeaderView::Fixed);
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
		int beginIndex=_model->player()->playlist().size();
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
			_model->player()->addMusic(obj);
		}
		_model->player()->asyncLoadInfo(beginIndex,_model->player()->playlist().size());
		_model->player()->playAt(beginIndex);
	}

}

void PlaylistWidget::on_clicked_clearButton()
{
	_model->player()->clearAllMusic();
}

int PlaylistWidget::headerY()
{
	return 30;
}
