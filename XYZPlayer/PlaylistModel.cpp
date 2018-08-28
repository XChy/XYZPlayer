#include "PlaylistModel.h"
#include <QDebug>

PlaylistModel::PlaylistModel(QObject* parent)
	:QAbstractTableModel(parent),
	  mPlayer(nullptr)
{

}

int PlaylistModel::rowCount(const QModelIndex& parent) const
{
	return mPlayer->playlist().size();
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
				return mPlayer->currentIndex()==index.row();
			case 1:
				return mPlayer->playlist()[index.row()].d->infoTags["title"];
			case 2:
				return mPlayer->playlist()[index.row()].d->infoTags["artist"];
			case 3:
				return mPlayer->playlist()[index.row()].d->duration;
		}
	}
	return QVariant();
}

Qt::DropActions PlaylistModel::supportedDropActions() const
{
	return Qt::CopyAction | Qt::MoveAction | Qt::TargetMoveAction;
}

Qt::ItemFlags PlaylistModel::flags(const QModelIndex& index) const
{
	Qt::ItemFlags defaultFlags = QAbstractTableModel::flags(index);
	return Qt::ItemIsDropEnabled | defaultFlags;
}

QStringList PlaylistModel::mimeTypes() const
{
	return {"text/url-list"};
}

bool PlaylistModel::canDropMimeData(const QMimeData* data, Qt::DropAction action, int row, int column, const QModelIndex& parent) const
{
	return data->hasUrls();
}

bool PlaylistModel::dropMimeData(const QMimeData* data, Qt::DropAction action, int row, int column, const QModelIndex& parent){
	if (action == Qt::IgnoreAction)
		return true;
	if (!data->hasUrls())
		return false;

	int insertIndex;
	if (row != -1)
		insertIndex = row;
	else if (parent.isValid())
		insertIndex = parent.row();
	else
		insertIndex = rowCount();

	for(QUrl url:data->urls()){
		MusicObject obj;
		obj.d->path=url.toLocalFile();
		obj.d->lyrics.path=url.toLocalFile().left(url.toLocalFile().indexOf('.')).append(".lrc");
		mPlayer->insertMusic(insertIndex,obj);
		mPlayer->asyncLoadInfo(insertIndex);
		mPlayer->asyncLoadPicture(insertIndex);
		mPlayer->asyncLoadLyrics(insertIndex);
		++insertIndex;
	}
	mPlayer->playAt(insertIndex-1);
	return true;
}

bool PlaylistModel::setData(const QModelIndex& index, const QVariant& v, int role)
{
	return false;
}

void PlaylistModel::refresh()
{
	beginResetModel();
	endResetModel();
}

MusicPlayer* PlaylistModel::player() const
{
	return mPlayer;
}

void PlaylistModel::setPlayer(MusicPlayer* player)
{
	if(player){
		connect(player,&MusicPlayer::currentIndexChanged,this,&PlaylistModel::refresh);
		connect(player,&MusicPlayer::loadedInfo,this,&PlaylistModel::refresh);
		connect(player,&MusicPlayer::playlistElementsChanged,this,&PlaylistModel::refresh);
	}
	if(mPlayer){
		disconnect(mPlayer,&MusicPlayer::currentIndexChanged,this,&PlaylistModel::refresh);
		disconnect(mPlayer,&MusicPlayer::loadedInfo,this,&PlaylistModel::refresh);
		disconnect(mPlayer,&MusicPlayer::playlistElementsChanged,this,&PlaylistModel::refresh);
	}
	mPlayer = player;
}
