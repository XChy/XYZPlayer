#ifndef MUSICPLAYER_H
#define MUSICPLAYER_H

#include <MusicObject.h>
#include <QtAV/QtAV>
#include <QList>

enum PlaybackType{
	Loop=0,
	CurrentItemLoop=1,
	Sequential=2,
	Random=3
};

class MusicPlayer : public QtAV::AVPlayer
{
public:
	MusicPlayer();
private:
	QList<MusicObject> mPlaylist;
};

#endif // MUSICPLAYER_H
