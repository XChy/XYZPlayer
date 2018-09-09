#include "LyricsModel.h"

LyricsModel::LyricsModel(QObject* parent)
	:QAbstractListModel(parent),
	  mPlayer(nullptr)
{

}

int LyricsModel::rowCount(const QModelIndex& parent) const
{
	return mPlayer->currentIndex()!=-1?mPlayer->currentMusic().d->lyrics.lyricList.size():0;
}

QVariant LyricsModel::data(const QModelIndex& index, int role) const
{
	if(!index.isValid()){
		return QVariant();
	}
	if(role==Qt::DisplayRole){
		return mPlayer->currentMusic().d->lyrics.lyricList[index.row()].second;
	}else if(role==Qt::UserRole){
		return index.row()==mLyricIndex;
	}
	return QVariant();
}

MusicPlayer* LyricsModel::player() const
{
	return mPlayer;
}

void LyricsModel::setPlayer(MusicPlayer* player)
{
	if(player){
		connect(player,&MusicPlayer::currentIndexChanged,this,&LyricsModel::refresh);
		connect(player,&MusicPlayer::loadedLyrics,this,&LyricsModel::refresh);
		connect(player,&MusicPlayer::positionChanged,this,&LyricsModel::onPositionChanged);
	}
	if(mPlayer){
		disconnect(mPlayer,&MusicPlayer::currentIndexChanged,this,&LyricsModel::refresh);
		disconnect(mPlayer,&MusicPlayer::loadedLyrics,this,&LyricsModel::refresh);
		disconnect(mPlayer,&MusicPlayer::positionChanged,this,&LyricsModel::onPositionChanged);
	}
	mPlayer = player;
}

bool LyricsModel::setData(const QModelIndex& index, const QVariant& v, int role)
{
	return false;
}

void LyricsModel::onPositionChanged(int64_t pos)
{
	if(!mPlayer->currentMusic().d->lyrics.lyricList.isEmpty()){
		if(mLyricIndex==mPlayer->currentMusic().d->lyrics.lyricList.size()-1){
			QPair<int64_t,QString> currentLyric=mPlayer->currentMusic().d->lyrics.lyricList[mLyricIndex];
			if(pos*1000<currentLyric.first&&mLyricIndex!=0){
				QPair<int64_t,QString> prevLyric=mPlayer->currentMusic().d->lyrics.lyricList[mLyricIndex-1];
				--mLyricIndex;
			}
		}else{
			QPair<int64_t,QString> nextLyric=mPlayer->currentMusic().d->lyrics.lyricList[mLyricIndex+1];
			if(pos*1000>=nextLyric.first){
				++mLyricIndex;
			}else{
				QPair<int64_t,QString> currentLyric=mPlayer->currentMusic().d->lyrics.lyricList[mLyricIndex];
				if(pos*1000<currentLyric.first&&mLyricIndex!=0){
					QPair<int64_t,QString> prevLyric=mPlayer->currentMusic().d->lyrics.lyricList[mLyricIndex-1];
					--mLyricIndex;
				}
			}
		}
	}
	emit dataChanged(index(mLyricIndex),index(mLyricIndex));
}

void LyricsModel::refresh()
{
	mLyricIndex=0;
	beginResetModel();
	endResetModel();
}
