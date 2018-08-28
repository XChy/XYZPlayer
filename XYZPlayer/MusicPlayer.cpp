#include "MusicPlayer.h"
#include <QDebug>


MusicPlayer::MusicPlayer(QObject* parent)
	:QtAV::AVPlayer(parent),
	  mCurrentIndex(-1),
	  mPlaybackMode(Loop)
{
	connect(this,&MusicPlayer::mediaStatusChanged,this,&MusicPlayer::onMediaStatusChanged);
}

QList<MusicObject> MusicPlayer::playlist() const
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
}

int MusicPlayer::currentIndex() const
{
	return mCurrentIndex;
}

void MusicPlayer::setCurrentIndex(int currentIndex)
{
	mCurrentIndex = currentIndex;
	if(mCurrentIndex!=-1){
		setFile(currentMusic().d->path);
	}else{
		setFile(QString());
	}
	emit currentIndexChanged(currentIndex);
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
			}
		}
	}else if(index<mCurrentIndex){
		--mCurrentIndex;
	}
	mPlaylist.removeAt(index);
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

bool MusicPlayer::canPlayback()
{
	switch (mPlaybackMode) {
		case Loop:
		case CurrentItemLoop:
		case Random:
			return !mPlaylist.isEmpty();

		case Sequential:
			return mCurrentIndex!=mPlaylist.size()-1;
	}
}

void MusicPlayer::loadInfo(int index)
{
	MusicUtil::loadInfo(mPlaylist[index]);
	emit loadedInfo(index);
}

void MusicPlayer::loadPicture(int index)
{
	MusicUtil::loadPicture(mPlaylist[index]);
	emit loadedPicture(index);
}

void MusicPlayer::loadLyrics(int index)
{
	MusicUtil::loadLyrics(mPlaylist[index]);
	emit loadedLyrics(index);
}

void MusicPlayer::asyncLoadInfo(int index)
{
	class Runnable:public QRunnable{
	public:
		Runnable(MusicPlayer* player,int index)
			:mPlayer(player),mIndex(index){}
		void run(){
			mPlayer->loadInfo(mIndex);
		}
		MusicPlayer* mPlayer;
		int mIndex;
	};
	Runnable* runnable=new Runnable(this,index);
	runnable->setAutoDelete(true);
	QThreadPool::globalInstance()->start(runnable);
}

void MusicPlayer::asyncLoadPicture(int index)
{
	class Runnable:public QRunnable{
	public:
		Runnable(MusicPlayer* player,int index)
			:mPlayer(player),mIndex(index){}
		void run(){
			mPlayer->loadPicture(mIndex);
		}
		MusicPlayer* mPlayer;
		int mIndex;
	};
	Runnable* runnable=new Runnable(this,index);
	runnable->setAutoDelete(true);
	QThreadPool::globalInstance()->start(runnable);
}

void MusicPlayer::asyncLoadLyrics(int index)
{
	class Runnable:public QRunnable{
	public:
		Runnable(MusicPlayer* player,int index)
			:mPlayer(player),mIndex(index){}
		void run(){
			mPlayer->loadLyrics(mIndex);
		}
		MusicPlayer* mPlayer;
		int mIndex;
	};
	Runnable* runnable=new Runnable(this,index);
	runnable->setAutoDelete(true);
	QThreadPool::globalInstance()->start(runnable);
}

void MusicPlayer::onMediaStatusChanged(QtAV::MediaStatus state)
{
	if(state==QtAV::EndOfMedia){
		playback();
	}
}



