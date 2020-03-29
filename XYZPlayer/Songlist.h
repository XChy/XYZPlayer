#ifndef SONGLIST_H
#define SONGLIST_H

#include <QList>
#include <QDate>
#include <XYZPlayer/MusicObject.h>

//typedef  QList<MusicObject*> Songlist;

class Songlist:public QList<MusicObject>{
	public:
		QDate timeCreated() const;
		void setTimeCreated(const QDate& timeCreated);

		QString name() const;
		void setName(const QString& name);

		friend QDataStream& operator>>(QDataStream& in, Songlist& data){
			in>>data._name;
			in>>data._timeCreated;
			in>>*(QList<MusicObject>*)(&data);
			return in;

		}

		friend QDataStream& operator<<(QDataStream& out, const Songlist& data){
			return out<<data._name<<data._timeCreated<<*(QList<MusicObject>*)(&data);
		}

	private:
		QDate _timeCreated;
		QString _name;

};



typedef  QList<Songlist> Songlists;

#endif // SONGLIST_H








