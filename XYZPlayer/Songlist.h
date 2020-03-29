#ifndef SONGLIST_H
#define SONGLIST_H

#include <QList>
#include <QDate>
#include <XYZPlayer/MusicObject.h>

//typedef  QList<MusicObject*> Songlist;

class Songlist:public QList<MusicObject*>{
	public:
		QDate timeCreated() const;
		void setTimeCreated(const QDate& timeCreated);

		QString name() const;
		void setName(const QString& name);

	private:
		QDate _timeCreated;
		QString _name;

};

typedef  QList<Songlist> Songlists;

#endif // SONGLIST_H








