#ifndef MUSICPLAYER_H
#define MUSICPLAYER_H

#include <QtAV/QtAV>
#include <QThreadPool>
#include <QList>
#include <QtConcurrentMap>
#include <QtConcurrentRun>
#include <QFutureWatcher>
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

	void removeMusic(int index);

	void playAt(int index);
	void playNext();
	void playPrev();

	void playback();
	bool canPlayback() const;

	const QFutureWatcher<int>& infoLoaderWatcher() const;

public slots:
	void loadInfo(int index);

	void loadPicture(int index);
	void loadLyrics(int index);

	void unLoadInfo(int index);
	void unLoadPicture(int index);
	void unLoadLyrics(int index);

	void asyncLoadInfo(int index);
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
private:
	void onMediaStatusChanged(QtAV::MediaStatus state);
private:
	QList<MusicObject> mPlaylist;
	QFutureWatcher<int> mInfoLoaderWatcher;
	QFutureWatcher<int> mPictureLoaderWatcher;
	int mInfoBeginLoadIndex;
	int mPictureBeginLoadIndex;
	int mCurrentIndex;
	PlaybackMode mPlaybackMode;
};

#endif // MUSICPLAYER_H
