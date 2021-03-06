#ifndef PLAYEREVENT_H
#define PLAYEREVENT_H

#include <QList>
#include <QPoint>
#include <QByteArray>
#include <QDataStream>
#include "Event.h"

typedef quint8 BitType;
typedef QPair<BitType,qint32> Cell;
typedef QList<Cell> Package;

class PlayerEvent:public Event
{
private:
	QPoint position;
	Package package;

	QString name;
	QString occupation;

public:
	PlayerEvent(const QByteArray &data=QByteArray())
	{
		if(!data.isEmpty()){
			QDataStream stream(data);
			EventType type;
			stream>>type;
			if(type==Player){
				stream>>position>>package>>name>>occupation;
			}
		}
	}

	QByteArray toByteArray() const
	{
		QByteArray data;
		QDataStream stream(&data,QIODevice::WriteOnly);
		EventType type=Player;
		stream<<type<<position<<package<<name<<occupation;
		return data;
	}

	inline const QPoint &getPosition() const {return position;}
	inline void setPosition(const QPoint &position){this->position=position;}

	inline const Package &getPackage() const {return package;}
	inline void setPackege(const Package &package){this->package=package;}

	inline const QString &getName() const {return name;}
	inline void setName(QString name){this->name=name;}

	inline const QString &getOccupation() const {return occupation;}
	inline void setOccupation(QString occupation){this->occupation=occupation;}
};

#endif // PLAYEREVENT_H
