#ifndef MUSICPLAYER_H
#define MUSICPLAYER_H

extern "C"{
#include <libavformat/avformat.h>
}

#include <QtAV/QtAV>
#include <QThreadPool>
#include <QList>
#include <QRunnable>
#include <XYZPlayer/MusicObject.h>

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
	MusicPlayer();

	QList<MusicObject> playlist() const;
	void setPlaylist(const QList<MusicObject>& playlist);

	PlaybackMode playbackMode() const;
	void setPlaybackMode(const PlaybackMode& playbackMode);

	int currentIndex() const;
	void setCurrentIndex(int currentIndex);

	MusicObject& currentMusic();

	void addMusic(const MusicObject& obj);
	void addMusicToCurrent(const MusicObject& obj);

	void playAt(int index);
	void playNext();
	void playPrev();

	void playback();
	bool canPlayback();

	void loadInfo(int index);
	void loadPicture(int index);

	void asyncLoadInfo(int index);
	void asyncLoadPicture(int index);
signals:
	void currentIndexChanged(int);
	void loadedInfo(int);
	void loadedPicture(int);
private:
	void onMediaStatusChanged(QtAV::MediaStatus state);
private:
	QList<MusicObject> mPlaylist;
	int mCurrentIndex;
	PlaybackMode mPlaybackMode;
};

#endif // MUSICPLAYER_H
