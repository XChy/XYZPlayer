#include "ui_LocalMusicWidget.h"
#include "LocalMusicWidget.h"

LocalMusicWidget::LocalMusicWidget(QWidget *parent)
	: QWidget(parent),
	  ui(new Ui::LocalMusicWidget),
	  _model(new SonglistsModel(this))
{
	ui->setupUi(this);
	MusicUtil::loadSonglists(&_local);
	_model->setSonglists(&_local);
	ui->view->setModel(_model);
}

LocalMusicWidget::~LocalMusicWidget()
{
	MusicUtil::saveSonglists(&_local);
	delete ui;
}

void LocalMusicWidget::on_addButton_clicked()
{
	AddSonglistDialog dialog;
	if(dialog.exec()){
		QString name=dialog.songlistName();
		if(name.isEmpty()){
			QMessageBox::warning(this,tr("Empty name!"),tr("Empty name is illegal"));
			return;
		}
		for(Songlist& list:_local){
			if(list.name()==name){
				QMessageBox::warning(this,tr("Duplication of name!"),tr("This name of songlist is duplicated"));
				return;
			}
		}

		Songlist list;
		list.setName(name);
		list.setTimeCreated(QDate::currentDate());
		_local.append(list);
		_model->refresh();
	}
}

Songlists& LocalMusicWidget::localSongs()
{
	return _local;
}

Songlists LocalMusicWidget::localSongs() const
{
	return _local;
}

void LocalMusicWidget::setLocalSongs(const Songlists& localSongs)
{
	_local = localSongs;
}
