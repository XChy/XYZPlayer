#ifndef MUSICLOADER_H
#define MUSICLOADER_H

#include <QObject>

class MusicLoader : public QObject
{
		Q_OBJECT
	public:
		explicit MusicLoader(QObject *parent = nullptr);

	signals:

};

#endif // MUSICLOADER_H
