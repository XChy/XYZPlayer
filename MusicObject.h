#ifndef MUSICOBJECT_H
#define MUSICOBJECT_H

#include <QMap>
#include <QImage>

class MusicObject
{
public:
	MusicObject();

	QString path;
	//info
	QMap<QString,QString> infoTags;//title album artist etc.
	int64_t duration;//μs
	//picture
	QImage picture;
};

#endif // MUSICOBJECT_H
