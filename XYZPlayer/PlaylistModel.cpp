#include "PlaylistModel.h"

PlaylistModel::PlaylistModel(QObject* parent)
	:QAbstractTableModel(parent)
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

MusicPlayer* PlaylistModel::player() const
{
	return mPlayer;
}

void PlaylistModel::setPlayer(MusicPlayer* player)
{
	mPlayer = player;
}
