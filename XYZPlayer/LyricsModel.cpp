#include "LyricsModel.h"

LyricsModel::LyricsModel(QObject* parent)
	:QAbstractListModel(parent),
	  mPlayer(nullptr),
	  lyricIndex(0)
{
}

int LyricsModel::rowCount(const QModelIndex& parent) const
{
	return mPlayer->currentIndex()!=-1?mPlayer->currentMusic().lyrics.lyricList.size():0;
}

QVariant LyricsModel::data(const QModelIndex& index, int role) const
{
	if(!index.isValid()){
		return QVariant();
	}
	if(role==Qt::DisplayRole){
		return mPlayer->currentMusic().lyrics.lyricList[index.row()].second;
	}else if(role==Qt::UserRole){
		return index.row()==lyricIndex;
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
		connect(player,&MusicPlayer::currentIndexChanged,this,&LyricsModel::onCurrentIndexChanged);
		connect(player,&MusicPlayer::lyricsLoaded,this,&LyricsModel::refresh);
		connect(player,&MusicPlayer::positionChanged,this,&LyricsModel::onPositionChanged);
	}
	if(mPlayer){
		disconnect(mPlayer,&MusicPlayer::currentIndexChanged,this,&LyricsModel::onCurrentIndexChanged);
		disconnect(mPlayer,&MusicPlayer::lyricsLoaded,this,&LyricsModel::refresh);
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
	auto& lyricsList=mPlayer->currentMusic().lyrics.lyricList;
	if(lyricsList.isEmpty()){
		return;
	}else if(lyricsList.first().first>pos){
		lyricIndex=0;
	}else if(lyricsList.last().first<pos){
		lyricIndex=lyricsList.size()-1;
	}else{
		if(lyricIndex!=lyricsList.size()-1&&pos>=lyricsList[lyricIndex+1].first){
			++lyricIndex;
		}else if(pos>=lyricsList[lyricIndex].first){
			return;
		}else if(pos>=lyricsList[lyricIndex-1].first){
			--lyricIndex;
		}else{
			auto it=std::upper_bound(lyricsList.begin(),lyricsList.end(),QPair<int64_t,QString>(pos,QStringLiteral(""))
									 ,[](const QPair<int64_t,QString>& v1,const QPair<int64_t,QString>& v2){
				return v1.first<v2.first;
			});
			lyricIndex=it-lyricsList.begin()-1;
		}
	}
	emit lyricIndexChanged(index(lyricIndex));
	emit dataChanged(index(lyricIndex),index(lyricIndex));
}

void LyricsModel::onCurrentIndexChanged(int oldIndex, int newIndex)
{
	if(oldIndex==newIndex)return;
	if(oldIndex!=-1){
		mPlayer->unLoadLyrics(oldIndex);
	}
	if(newIndex!=-1){
		mPlayer->asyncLoadLyrics(newIndex);
	}else{
		refresh();
	}
}

void LyricsModel::refresh()
{
	lyricIndex=0;
	emit lyricIndexChanged(QModelIndex());
	beginResetModel();
	endResetModel();
}
