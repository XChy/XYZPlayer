#include "PlaylistModel.h"
#include <QDebug>

PlaylistModel::PlaylistModel(QObject* parent)
	:QAbstractTableModel(parent),
	  _player(nullptr)
{

}

int PlaylistModel::rowCount(const QModelIndex& parent) const
{
	return _player->playlist().size();
}

int PlaylistModel::columnCount(const QModelIndex& parent) const
{
	return 4;
}

QVariant PlaylistModel::data(const QModelIndex& index, int role) const
{
	if(role==Qt::DisplayRole){
		if(!index.isValid()){
			return QVariant();
		}
		switch(index.column()){
			case 0:
				return _player->currentIndex()==index.row();
			case 1:
				return _player->playlist()[index.row()].infoTags["title"];
			case 2:
				return _player->playlist()[index.row()].infoTags["artist"];
			case 3:
				return _player->playlist()[index.row()].duration;
		}
	}
	return QVariant();
}

Qt::DropActions PlaylistModel::supportedDropActions() const
{
	return Qt::CopyAction | Qt::MoveAction;
}

Qt::DropActions PlaylistModel::supportedDragActions() const
{
	return Qt::MoveAction;
}

Qt::ItemFlags PlaylistModel::flags(const QModelIndex& index) const
{
	Qt::ItemFlags defaultFlags = QAbstractTableModel::flags(index);
	return Qt::ItemIsDropEnabled| Qt::ItemIsDragEnabled | defaultFlags;
}

QStringList PlaylistModel::mimeTypes() const
{
	return {"text/url-list"};
}

QMimeData* PlaylistModel::mimeData(const QModelIndexList& indexes) const
{
	QMimeData* data=new QMimeData;
	return data;
}

bool PlaylistModel::canDropMimeData(const QMimeData* data, Qt::DropAction action, int row, int column, const QModelIndex& parent) const
{
	return data->hasUrls()||action==Qt::MoveAction;
}

bool PlaylistModel::dropMimeData(const QMimeData* data, Qt::DropAction action, int row, int column, const QModelIndex& parent){
	if (action == Qt::IgnoreAction)
		return true;
	if (data->hasUrls()){

		int insertIndex;
		if (row != -1)
			insertIndex = row;
		else if (parent.isValid())
			insertIndex = parent.row();
		else
			insertIndex = rowCount();

		int beginIndex=insertIndex;

		for(QUrl url:data->urls()){
			MusicObject obj;
			obj.path=url.toLocalFile();
			obj.lyrics.path=url.toLocalFile().left(url.toLocalFile().lastIndexOf('.')).append(".lrc");
			_player->insertMusic(insertIndex,obj);
			++insertIndex;
		}
		_player->asyncLoadInfo(beginIndex,insertIndex);
		_player->playAt(beginIndex);
		return true;
	}else if(action==Qt::MoveAction){

	}

	return false;
}

bool PlaylistModel::setData(const QModelIndex& index, const QVariant& v, int role)
{
	return false;
}

void PlaylistModel::onCurrentIndexChanged(int oldIndex, int newIndex)
{
	if(oldIndex==newIndex)return;
	if(oldIndex==-1){
		emit dataChanged(index(newIndex,0),index(newIndex,0));
	}else if(newIndex==-1){
		emit dataChanged(index(oldIndex,0),index(oldIndex,0));
	}else{
		emit dataChanged(index(oldIndex,0),index(oldIndex,0));
		emit dataChanged(index(newIndex,0),index(newIndex,0));
	}
}

void PlaylistModel::onInfoLoaded(int index)
{
	emit dataChanged(this->index(index,1),this->index(index,3));
}

void PlaylistModel::refresh()
{
	beginResetModel();
	endResetModel();
}

MusicPlayer* PlaylistModel::player() const
{
	return _player;
}

void PlaylistModel::setPlayer(MusicPlayer* player)
{
	if(player){
		connect(player,&MusicPlayer::currentIndexChanged,this,&PlaylistModel::onCurrentIndexChanged);
		connect(player,&MusicPlayer::infoLoaded,this,&PlaylistModel::onInfoLoaded);
		connect(player,&MusicPlayer::playlistElementsChanged,this,&PlaylistModel::refresh);
	}
	if(_player){
		disconnect(_player,&MusicPlayer::currentIndexChanged,this,&PlaylistModel::onCurrentIndexChanged);
		disconnect(_player,&MusicPlayer::infoLoaded,this,&PlaylistModel::onInfoLoaded);
		disconnect(_player,&MusicPlayer::playlistElementsChanged,this,&PlaylistModel::refresh);
	}
	_player = player;
}
