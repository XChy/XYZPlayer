#ifndef MUSICPLAYER_H
#define MUSICPLAYER_H

#include <QtAV/QtAV>
#include <QThreadPool>
#include <QList>
#include <QRunnable>
#include <QFileInfo>
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
	void setPlaylist(const QList<MusicObject>& playlist);

	PlaybackMode playbackMode() const;
	void setPlaybackMode(const PlaybackMode& playbackMode);

	int currentIndex() const;
	void setCurrentIndex(int currentIndex);

	MusicObject& currentMusic();

	void addMusic(const MusicObject& obj);
	void addMusicToCurrent(const MusicObject& obj);

	void insertMusic(int index, const MusicObject& obj);

	void removeMusic(int index);

	void playAt(int index);
	void playNext();
	void playPrev();

	void playback();
	bool canPlayback();
public slots:
	void loadInfo(int index);
	void loadPicture(int index);
	void loadLyrics(int index);

	void asyncLoadInfo(int index);
	void asyncLoadPicture(int index);
	void asyncLoadLyrics(int index);
signals:
	void currentIndexChanged(int index);
	void playlistElementsChanged();
	void loadedInfo(int index);
	void loadedPicture(int index);
	void loadedLyrics(int index);
private:
	void onMediaStatusChanged(QtAV::MediaStatus state);
private:
	QList<MusicObject> mPlaylist;
	int mCurrentIndex;
	PlaybackMode mPlaybackMode;
};

#endif // MUSICPLAYER_H
