#include "MusicPlayer.h"

MusicPlayer::MusicPlayer()
	:mCurrentIndex(-1),
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
	setFile(mPlaylist[currentIndex].path);
	emit currentIndexChanged(currentIndex);
}

void MusicPlayer::addMusic(const MusicObject& obj)
{
	mPlaylist.append(obj);
}

void MusicPlayer::addMusicToCurrent(const MusicObject& obj)
{
	addMusic(obj);
	setCurrentIndex(mPlaylist.size()-1);
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
	}
}

void MusicPlayer::playPrev()
{
	if(!mPlaylist.isEmpty()){
		playAt( mCurrentIndex!=0 ? mCurrentIndex-1 : mPlaylist.size()-1 );
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

void MusicPlayer::onMediaStatusChanged(QtAV::MediaStatus state)
{
	if(state==QtAV::EndOfMedia){
		playback();
	}
}



