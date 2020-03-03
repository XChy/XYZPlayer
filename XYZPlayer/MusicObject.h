#ifndef MUSICOBJECT_H
#define MUSICOBJECT_H

#include <QMap>
#include <QPixmap>
#include <QPixmapCache>
#include <QDataStream>

class LyricsObject{
public:
    QString path;

	QList<QPair<int64_t,QString>> lyricList;
    //int64_t:position unit:ms
    //int64_t:歌词所在位置    QString:歌词
};

class MusicObject
{
public:
	MusicObject();

	QString path;


    QMap<QString,QString> infoTags;
    //info:title album artist etc.
    //信息:标题 专辑 艺术家等
    int64_t duration=0;
    //unit:μs
    //单位:微秒

    QPixmap picture;

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
