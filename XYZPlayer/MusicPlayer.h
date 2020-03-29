#ifndef MUSICPLAYER_H
#define MUSICPLAYER_H

#include <QtAV/QtAV>
#include <QList>
#include <QFileInfo>
#include <XYZPlayer/MusicLoader.h>
#include <XYZPlayer/MusicObject.h>
#include <XYZPlayer/MusicUtil.h>

enum PlaybackMode{
	Loop,
	CurrentItemLoop,
	Sequential,
	Random
};

class MusicPlayer : public QtAV::AVPlayer
{
	Q_OBJECT
public:
	MusicPlayer(QObject* parent=nullptr);

	QList<MusicObject> playlist() const;
	QList<MusicObject>& playlist();
	void setPlaylist(const QList<MusicObject>& playlist);

	PlaybackMode playbackMode() const;
	void setPlaybackMode(const PlaybackMode& playbackMode);

	int currentIndex() const;
	void setCurrentIndex(int currentIndex);

	MusicObject& currentMusic();

	void addMusic(const MusicObject& obj);
	void addMusicToCurrent(const MusicObject& obj);

	void insertMusic(int index, const MusicObject& obj);

	void moveMusic(int from, int to);
	void moveMusics(int from,int len, int to);

	//删除过快时,异步资源加载会出现bug
	void removeMusic(int index);
	//含头不含尾
	void removeMusics(int begin,int end);

    void clearAllMusic();

	void playAt(int index);
	void playNext();
	void playPrev();

	void playback();
	bool canPlayback() const;

public slots:
	void loadInfo(int index);

	void loadPicture(int index);
	void loadLyrics(int index);

	void unLoadInfo(int index);
	void unLoadPicture(int index);
	void unLoadLyrics(int index);

	void asyncLoadInfo(int index);

	//含头不含尾
	void asyncLoadInfo(int begin,int end);
	void asyncLoadAllInfo();

	void asyncLoadPicture(int index);
	void asyncLoadLyrics(int index);
signals:
	void currentIndexChanged(int oldIndex,int newIndex);
	void playlistElementsChanged();
	void infoLoaded(int index);
	void pictureLoaded(int index);
	void lyricsLoaded(int index);

	void playbackModeChanged(PlaybackMode mode);
private:
	void onMediaStatusChanged(QtAV::MediaStatus state);
private:
	QList<MusicObject> _playlist;
	MusicLoader* _loader;
	int _currentIndex;
	PlaybackMode _playbackMode;
};

#endif // MUSICPLAYER_H
