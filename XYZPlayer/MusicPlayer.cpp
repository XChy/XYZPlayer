#include "MusicPlayer.h"
#include <QDebug>

MusicPlayer::MusicPlayer(QObject* parent)
	:QtAV::AVPlayer(parent),
	  _currentIndex(-1),
	  _playbackMode(Loop),
	  _loader(new MusicLoader(this))
{
	setAutoLoad();
	connect(this,&MusicPlayer::mediaStatusChanged,this,&MusicPlayer::onMediaStatusChanged);
	connect(_loader,&MusicLoader::infoLoaded,[this](MusicObject* obj){
		emit infoLoaded(_playlist.indexOf(*obj));
	});
	connect(_loader,&MusicLoader::pictureLoaded,[this](MusicObject* obj){
		emit pictureLoaded(_playlist.indexOf(*obj));
	});
	connect(_loader,&MusicLoader::lyricsLoaded,[this](MusicObject* obj){
		emit lyricsLoaded(_playlist.indexOf(*obj));
	});
}

QList<MusicObject> MusicPlayer::playlist() const
{
	return _playlist;
}

QList<MusicObject>& MusicPlayer::playlist()
{
	return _playlist;
}

void MusicPlayer::setPlaylist(const QList<MusicObject>& playlist)
{
	_playlist = playlist;
}


PlaybackMode MusicPlayer::playbackMode() const
{
	return _playbackMode;
}

void MusicPlayer::setPlaybackMode(const PlaybackMode& playbackMode)
{
	_playbackMode = playbackMode;
	emit playbackModeChanged(playbackMode);
}

int MusicPlayer::currentIndex() const
{
	return _currentIndex;
}

void MusicPlayer::setCurrentIndex(int currentIndex)
{
	int oldIndex=_currentIndex;
	_currentIndex = currentIndex;
	if(_currentIndex!=-1){
		setFile(currentMusic().path);
	}else{
		setFile(QString());
		stop();
	}
	emit currentIndexChanged(oldIndex,currentIndex);
}

MusicObject& MusicPlayer::currentMusic()
{
	return _playlist[_currentIndex];
}

void MusicPlayer::addMusic(const MusicObject& obj)
{
	_playlist.append(obj);
	emit playlistElementsChanged();
}

void MusicPlayer::addMusicToCurrent(const MusicObject& obj)
{
	addMusic(obj);
	emit playlistElementsChanged();
	setCurrentIndex(_playlist.size()-1);
}

void MusicPlayer::insertMusic(int index,const MusicObject& obj)
{
	_playlist.insert(index,obj);
	if(index<_currentIndex){
		++_currentIndex;
	}
	emit playlistElementsChanged();
}

void MusicPlayer::moveMusic(int from, int to)
{
	MusicObject& obj=currentMusic();
	_playlist.move(from,to);
	_currentIndex=_playlist.indexOf(obj);
	emit playlistElementsChanged();
}

void MusicPlayer::moveMusics(int from, int len, int to)
{
	MusicObject& obj=currentMusic();
	_playlist.move(from,to);
	_currentIndex=_playlist.indexOf(obj);
	emit playlistElementsChanged();
}

void MusicPlayer::removeMusic(int index)
{
	if(_currentIndex==index){
		if(_playlist.size()==1){
			setCurrentIndex(-1);
			stop();
		}else{
			playNext();
			if(_currentIndex){
				--_currentIndex;
				emit currentIndexChanged(-1,_currentIndex);
			}
		}
	}else if(index<_currentIndex){
		--_currentIndex;
	}
	_playlist.removeAt(index);
	emit playlistElementsChanged();
}

void MusicPlayer::removeMusics(int begin, int end)
{
	//currentIndex 属于 [begin,end)时
	int size=end-begin;
	MusicObject* current=&currentMusic();
	if(_currentIndex>=begin&&_currentIndex<end){
		if(_playlist.size()==size){
			setCurrentIndex(-1);
			_playlist.erase(_playlist.begin()+begin,_playlist.begin()+end);//erase也是含头不含尾
			stop();
		}else{
			setCurrentIndex(-1);
			if(_playlist.size()==end){
				_playlist.erase(_playlist.begin()+begin,_playlist.begin()+end);//erase也是含头不含尾
				playAt(0);
			}else{
				_playlist.erase(_playlist.begin()+begin,_playlist.begin()+end);//erase也是含头不含尾
				playAt(begin);
			}
		}
	}else if(_currentIndex<begin){
		_playlist.erase(_playlist.begin()+begin,_playlist.begin()+end);
	}else if(end<=_currentIndex){
		_currentIndex -= size;
		_playlist.erase(_playlist.begin()+begin,_playlist.begin()+end);//erase也是含头不含尾
	}
	emit playlistElementsChanged();
}

void MusicPlayer::clearAllMusic()
{
	setCurrentIndex(-1);
	_playlist.clear();
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
	if(!_playlist.isEmpty()){
		playAt( _currentIndex!=_playlist.size()-1 ? _currentIndex+1 : 0 );
	}else{
		setCurrentIndex(-1);
	}
}

void MusicPlayer::playPrev()
{
	if(!_playlist.isEmpty()){
		playAt( _currentIndex!=0 ? _currentIndex-1 : _playlist.size()-1 );
	}else{
		setCurrentIndex(-1);
	}
}

void MusicPlayer::playback()
{
	switch (_playbackMode) {
	case Loop:
		playNext();
		break;
	case CurrentItemLoop:
		playAt(_currentIndex);
		break;
	case Sequential:
		if(_currentIndex!=_playlist.size()-1){
			playAt(_currentIndex+1);
		}
		break;
	case Random:
		if(!_playlist.isEmpty()){
			playAt(qrand()%_playlist.size());
		}
		break;
	}
}

bool MusicPlayer::canPlayback() const
{
	switch (_playbackMode) {
	case Loop:
	case CurrentItemLoop:
	case Random:
		return !_playlist.isEmpty();

	case Sequential:
		return _currentIndex!=_playlist.size()-1;
	}
	return false;
}

void MusicPlayer::loadInfo(int index)
{
	MusicUtil::loadInfo(_playlist[index]);
	emit infoLoaded(index);
}
void MusicPlayer::loadPicture(int index)
{
	MusicUtil::loadPicture(_playlist[index]);
	emit pictureLoaded(index);
}

void MusicPlayer::loadLyrics(int index)
{
	MusicUtil::LyricsError error=MusicUtil::loadLyrics(_playlist[index]);
	if(!error){

	}
	emit lyricsLoaded(index);
}

void MusicPlayer::asyncLoadInfo(int index)
{
	_loader->asyncLoadInfo(&_playlist[index]);
}

void MusicPlayer::asyncLoadInfo(int begin, int end)
{
	for(int i=begin;i<end;++i){
		_loader->asyncLoadInfo(&_playlist[i]);
	}
}

void MusicPlayer::asyncLoadAllInfo()
{
	for(int i=0;i<_playlist.size();++i){
		_loader->asyncLoadInfo(&_playlist[i]);
	}
}

void MusicPlayer::asyncLoadPicture(int index)
{
	_loader->asyncLoadPicture(&_playlist[index]);
}

void MusicPlayer::asyncLoadLyrics(int index)
{
	_loader->asyncLoadLyrics(&_playlist[index]);
}

void MusicPlayer::unLoadInfo(int index)
{
	_loader->unLoadInfo(&_playlist[index]);
}

void MusicPlayer::unLoadPicture(int index)
{
	_loader->unLoadPicture(&_playlist[index]);
}

void MusicPlayer::unLoadLyrics(int index)
{
	_loader->unLoadLyrics(&_playlist[index]);
}

void MusicPlayer::onMediaStatusChanged(QtAV::MediaStatus state)
{
	if(state==QtAV::EndOfMedia){
		playback();
	}
}




