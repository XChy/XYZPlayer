#include <XYZPlayer/Songlist.h>

QDate Songlist::timeCreated() const
{
	return _timeCreated;
}


void Songlist::setTimeCreated(const QDate& timeCreated)
{
	_timeCreated = timeCreated;
}

QString Songlist::name() const
{
	return _name;
}

void Songlist::setName(const QString& name)
{
	_name = name;
}
