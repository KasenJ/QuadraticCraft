#ifndef PLAYEREVENT_H
#define PLAYEREVENT_H

#include <QList>
#include <QPoint>
#include <QByteArray>
#include <QDataStream>
#include "Bit.h"
#include "Event.h"

typedef QList< QPair<BitType,qint8> > Package;

class PlayerEvent:public Event
{
private:
	QPoint position;
	Package package;

public:
	PlayerEvent(const QByteArray &data=QByteArray())
	{
		if(!data.isEmpty()){
			QDataStream stream(data);
			EventType type;
			stream>>type;
			if(type==Player){
				stream>>position>>package;
			}
		}
	}

	QByteArray toByteArray() const
	{
		QByteArray data;
		QDataStream stream(&data,QIODevice::WriteOnly);
		EventType type=Player;
		stream<<type<<position<<package;
		return data;
	}

	inline const QPoint &getPosition() const {return position;}
	inline void setPosition(const QPoint &position){this->position=position;}

	inline const Package &getPackage() const {return package;}
	inline void setPackege(const Package &package){this->package=package;}
};

#endif // PLAYEREVENT_H
