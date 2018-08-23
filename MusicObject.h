#ifndef MUSICOBJECT_H
#define MUSICOBJECT_H

#include <QMap>
#include <QPixmap>

class MusicObject
{
public:
	MusicObject();

	QString path;
	QMap<QString,QString> info;
	QPixmap picture;
};

#endif // MUSICOBJECT_H
