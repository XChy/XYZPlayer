#include "MusicPlayer.h"
#include <QDebug>

MusicPlayer::MusicPlayer(QObject* parent)
	:QtAV::AVPlayer(parent),
	  mCurrentIndex(-1),
	  mPlaybackMode(Loop),
	  mInfoBeginLoadIndex(0),
	  mPictureBeginLoadIndex(0)
{
	setAutoLoad();
	mInfoLoaderWatcher.setPendingResultsLimit(3);
	connect(this,&MusicPlayer::mediaStatusChanged,this,&MusicPlayer::onMediaStatusChanged);

	connect(&mInfoLoaderWatcher,&QFutureWatcher<int>::resultReadyAt,[this](int index){
		emit infoLoaded(mInfoBeginLoadIndex+index);
	});

	mPictureLoaderWatcher.setPendingResultsLimit(3);
	connect(&mPictureLoaderWatcher,&QFutureWatcher<int>::resultReadyAt,[this](int index){
		emit pictureLoaded(mPictureBeginLoadIndex+index);
	});
}

QList<MusicObject> MusicPlayer::playlist() const
{
	return mPlaylist;
}

QList<MusicObject>& MusicPlayer::playlist()
{
	return mPlaylist;
}

void MusicPlayer::setPlaylist(const QList<MusicObject>& playlist)
{
	mPlaylist = playlist;
}


PlaybackMode MusicPlayer::playbackMode() const
{
	return mPlaybackMode;
}

void MusicPlayer::setPlaybackMode(const PlaybackMode& playbackMode)
{
	mPlaybackMode = playbackMode;
	emit playbackModeChanged(playbackMode);
}

int MusicPlayer::currentIndex() const
{
	return mCurrentIndex;
}

void MusicPlayer::setCurrentIndex(int currentIndex)
{
	int oldIndex=mCurrentIndex;
    mCurrentIndex = currentIndex;
	if(mCurrentIndex!=-1){
		setFile(currentMusic().path);
    }else{
        setFile(QString());
        stop();
    }
	emit currentIndexChanged(oldIndex,currentIndex);
}

MusicObject& MusicPlayer::currentMusic()
{
	return mPlaylist[mCurrentIndex];
}

void MusicPlayer::addMusic(const MusicObject& obj)
{
	mPlaylist.append(obj);
	emit playlistElementsChanged();
}

void MusicPlayer::addMusicToCurrent(const MusicObject& obj)
{
	addMusic(obj);
	emit playlistElementsChanged();
	setCurrentIndex(mPlaylist.size()-1);
}

void MusicPlayer::insertMusic(int index,const MusicObject& obj)
{
	mPlaylist.insert(index,obj);
	if(index<mCurrentIndex){
		++mCurrentIndex;
	}
	emit playlistElementsChanged();
}

void MusicPlayer::removeMusic(int index)
{
	if(mCurrentIndex==index){
		if(mPlaylist.size()==1){
			setCurrentIndex(-1);
			stop();
		}else{
			playNext();
			if(mCurrentIndex){
				--mCurrentIndex;
				emit currentIndexChanged(-1,mCurrentIndex);
			}
		}
	}else if(index<mCurrentIndex){
		--mCurrentIndex;
	}
	mPlaylist.removeAt(index);
    emit playlistElementsChanged();
}

void MusicPlayer::clearAllMusic()
{
    setCurrentIndex(-1);
    mPlaylist.clear();
    emit playlistElementsChanged();
}

void MusicPlayer::playAt(int index)
{
	stop();
	setCurrentIndex(index);
	play();
}

void MusicPlayer::playNext()
{
	if(!mPlaylist.isEmpty()){
		playAt( mCurrentIndex!=mPlaylist.size()-1 ? mCurrentIndex+1 : 0 );
	}else{
		setCurrentIndex(-1);
	}
}

void MusicPlayer::playPrev()
{
	if(!mPlaylist.isEmpty()){
		playAt( mCurrentIndex!=0 ? mCurrentIndex-1 : mPlaylist.size()-1 );
	}else{
		setCurrentIndex(-1);
	}
}

void MusicPlayer::playback()
{
	switch (mPlaybackMode) {
		case Loop:
			playNext();
			break;
		case CurrentItemLoop:
			playAt(mCurrentIndex);
			break;
		case Sequential:
			if(mCurrentIndex!=mPlaylist.size()-1){
				playAt(mCurrentIndex+1);
			}
			break;
		case Random:
			if(!mPlaylist.isEmpty()){
				playAt(qrand()%mPlaylist.size());
			}
			break;
	}
}

bool MusicPlayer::canPlayback() const
{
	switch (mPlaybackMode) {
		case Loop:
		case CurrentItemLoop:
		case Random:
			return !mPlaylist.isEmpty();

		case Sequential:
			return mCurrentIndex!=mPlaylist.size()-1;
	}
	return false;
}

void MusicPlayer::loadInfo(int index)
{
	MusicUtil::loadInfo(mPlaylist[index]);
	emit infoLoaded(index);
}
void MusicPlayer::loadPicture(int index)
{
	MusicUtil::loadPicture(mPlaylist[index]);
	emit pictureLoaded(index);
}

void MusicPlayer::loadLyrics(int index)
{
	MusicUtil::loadLyrics(mPlaylist[index]);
	emit lyricsLoaded(index);
}

void MusicPlayer::asyncLoadInfo(int index)
{
	QtConcurrent::run(this,&MusicPlayer::loadInfo,index);
}

void MusicPlayer::asyncLoadInfo(int begin, int end)
{
	mInfoBeginLoadIndex=begin;
	mInfoLoaderWatcher.setFuture(QtConcurrent::mapped(mPlaylist.begin()+begin,mPlaylist.begin()+end,MusicUtil::loadInfo));
}

void MusicPlayer::asyncLoadAllInfo()
{
	mInfoBeginLoadIndex=0;
	mInfoLoaderWatcher.setFuture(QtConcurrent::mapped(mPlaylist.begin(),mPlaylist.end(),MusicUtil::loadInfo));
}

void MusicPlayer::asyncLoadPicture(int index)
{
	QtConcurrent::run(this,&MusicPlayer::loadPicture,index);
}

void MusicPlayer::asyncLoadLyrics(int index)
{
	QtConcurrent::run(this,&MusicPlayer::loadLyrics,index);
}

void MusicPlayer::unLoadInfo(int index)
{
	mPlaylist[index].infoTags.clear();
	mPlaylist[index].duration=0;
}

void MusicPlayer::unLoadPicture(int index)
{
	if(mPictureLoaderWatcher.isRunning())
		mPictureLoaderWatcher.cancel();
    mPlaylist[index].picture=QPixmap();
}

void MusicPlayer::unLoadLyrics(int index)
{
	mPlaylist[index].lyrics.lyricList.clear();
}

void MusicPlayer::onMediaStatusChanged(QtAV::MediaStatus state)
{
	if(state==QtAV::EndOfMedia){
		playback();
	}
}

const QFutureWatcher<int>& MusicPlayer::infoLoaderWatcher() const
{
	return mInfoLoaderWatcher;
}



