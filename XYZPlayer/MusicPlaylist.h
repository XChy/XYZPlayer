#ifndef MUSICPLAYLIST_H
#define MUSICPLAYLIST_H

#include <QList>
#include <QObject>
#include <XYZPlayer/MusicObject.h>
#include <XYZPlayer/MusicUtil.h>

class MusicPlaylist:public QObject
{
public:
	MusicPlaylist();
public slots:
	void addMusic();
signals:
	QList<MusicObject> mData;
};

#endif // MUSICPLAYLIST_H
