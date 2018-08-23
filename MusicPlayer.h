#ifndef MUSICPLAYER_H
#define MUSICPLAYER_H

#include <MusicObject.h>
#include <QtAV/QtAV>
#include <QList>

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

	void addMusic(const MusicObject& obj);
	void addMusicToCurrent(const MusicObject& obj);

	void playAt(int index);
	void playNext();
	void playPrev();

	void playback();
	bool canPlayback();
signals:
	void currentIndexChanged(int);
private:
	void onMediaStatusChanged(QtAV::MediaStatus state);
private:
	QList<MusicObject> mPlaylist;
	int mCurrentIndex;
	PlaybackMode mPlaybackMode;
};

#endif // MUSICPLAYER_H
