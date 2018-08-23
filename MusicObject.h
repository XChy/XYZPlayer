#ifndef MUSICOBJECT_H
#define MUSICOBJECT_H

#include <QMap>
#include <QImage>

class MusicObject
{
public:
	MusicObject();

	QString path;
	QMap<QString,QString> info;
	QImage picture;
};

#endif // MUSICOBJECT_H
