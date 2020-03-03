#include "LyricsWidget.h"

LyricsWidget::LyricsWidget(QWidget *parent)
	: QWidget(parent),
	  _tipLabel(new QLabel(this)),
	  _model(new LyricsModel(this)),
	  _view(new LyricsView(this)),
	  _chooseButton(new QPushButton(this)),
	  _player(nullptr)
{
	_view->move(0,0);
	_view->setResizeMode(QListView::Adjust);
	_view->setItemDelegate(new LyricItemDelegate(this));

	_tipLabel->move(0,0);
	_tipLabel->setWordWrap(true);
	_tipLabel->raise();
	_tipLabel->hide();
	_tipLabel->setAlignment(Qt::AlignCenter);
	_tipLabel->setText(tr("No lyrics found, Please click the button to choose lyrics"));

	_chooseButton->setText(tr("Choose lyrics"));
	_chooseButton->raise();
	_chooseButton->move(width()-_chooseButton->width(),
						height()-_chooseButton->height());

	connect(_chooseButton,&QPushButton::clicked,this,&LyricsWidget::onChooseLyrics);
}

void LyricsWidget::resizeEvent(QResizeEvent* e)
{
	_tipLabel->setFixedSize(size());
	_view->setFixedSize(size());
	_chooseButton->move(width()-_chooseButton->width(),
						height()-_chooseButton->height());
}

MusicPlayer* LyricsWidget::player() const
{
	return _player;
}

void LyricsWidget::setPlayer(MusicPlayer* player)
{
	_model->setPlayer(player);
	_view->setModel(_model);
	if(_player){
		disconnect(_player,&MusicPlayer::currentIndexChanged,this,&LyricsWidget::updateTipLabel);
		disconnect(_player,&MusicPlayer::lyricsLoaded,this,&LyricsWidget::updateTipLabel);
	}
	if(player){
		connect(player,&MusicPlayer::currentIndexChanged,this,&LyricsWidget::updateTipLabel);
		connect(player,&MusicPlayer::lyricsLoaded,this,&LyricsWidget::updateTipLabel);
	}
	_player = player;
}

void LyricsWidget::onChooseLyrics()
{
	QSettings setting("../data/settings.ini",QSettings::IniFormat);
	QFileDialog dialog(this,tr("Set lyrics"),setting.value("LyricsFileDialog/open_dir",QString()).toString());
	dialog.setAcceptMode(QFileDialog::AcceptOpen);
	dialog.setFileMode(QFileDialog::ExistingFile);
	if(dialog.exec())
	{
		QString file = dialog.selectedFiles().first();
		if(file.isEmpty()){
			return;
		}else{
			setting.beginGroup("LyricsFileDialog");
			setting.setValue("open_dir",dialog.directory().path());
			setting.endGroup();
			player()->currentMusic().lyrics.path=file;
			_player->loadLyrics(_player->currentIndex());

		}
	}
}

void LyricsWidget::updateTipLabel()
{
	if(_player->currentIndex()!=-1 && _player->currentMusic().lyrics.lyricList.isEmpty()){
		_tipLabel->show();
	}else{
		_tipLabel->hide();
	}
}
