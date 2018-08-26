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
		if(index.column()<0||index.column()>columnCount()-1||index.row()<0||index.row()>rowCount()-1){
			return QVariant();
		}
		switch(index.column()){
			case 0:
				return mPlayer->currentIndex()==index.row();
			case 1:
				return mPlayer->playlist()[index.row()].infoTags["title"];
			case 2:
				return mPlayer->playlist()[index.row()].infoTags["artist"];
			case 3:
				return mPlayer->playlist()[index.row()].duration;
		}
	}
	return QVariant();
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
		connect(player,&MusicPlayer::playlistElementsChanged,this,&PlaylistModel::refresh);
	}
	if(mPlayer){
		disconnect(mPlayer,&MusicPlayer::currentIndexChanged,this,&PlaylistModel::refresh);
		disconnect(mPlayer,&MusicPlayer::playlistElementsChanged,this,&PlaylistModel::refresh);
	}
	mPlayer = player;
}
