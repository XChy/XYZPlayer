#ifndef MUSICOBJECT_H
#define MUSICOBJECT_H

#include <QMap>
#include <QImage>
#include <QDataStream>

class LyricsObject{
public:
	QString path;
	QList<QPair<int64_t,QString>> lyricList;
	//int64_t:position unit:μs
};

class MusicObject
{
public:
	MusicObject();

	QString path;
	//info
	QMap<QString,QString> infoTags;//title album artist etc.
	int64_t duration=0;//unit:μs
	//picture
	QImage picture;
	//lyrics
	LyricsObject lyrics;

	friend QDataStream& operator>>(QDataStream& in, MusicObject& data)
	{
		in>>data.path>>data.lyrics.path;
		return in;
	}

	friend QDataStream& operator<<(QDataStream& out, const MusicObject& data)
	{
		out<<data.path<<data.lyrics.path;
		return out;
	}
};

#endif // MUSICOBJECT_H
