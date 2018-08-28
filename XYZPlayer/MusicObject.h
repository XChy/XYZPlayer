#ifndef MUSICOBJECT_H
#define MUSICOBJECT_H

#include <QMap>
#include <QImage>
#include <QSharedData>
#include <QExplicitlySharedDataPointer>

class LyricsObject{
public:
	QString path;
	QList<QPair<int64_t,QString>> lyricList;
};

class MusicSharedData:public QSharedData{
public:
	QString path;
	//info
	QMap<QString,QString> infoTags;//title album artist etc.
	int64_t duration=0;//μs
	//picture
	QImage picture;
	//lyrics
	LyricsObject lyrics;
};

class MusicObject
{
public:
	MusicObject();

	QExplicitlySharedDataPointer<MusicSharedData> d;
};

#endif // MUSICOBJECT_H
