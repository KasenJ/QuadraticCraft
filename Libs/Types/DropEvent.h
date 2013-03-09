#ifndef SETEVENT_H
#define SETEVENT_H

#include <QPoint>
#include <QByteArray>
#include <QDataStream>
#include "Event.h"
#include "Square.h"

class DropEvent:public Event
{
private:
	QPoint drop;
	BitType bit;

public:
	DropEvent(const QByteArray &data=QByteArray())
	{
		if(!data.isEmpty()){
			QDataStream stream(data);
			EventType type;
			stream>>type;
			if(type==Drop){
				stream>>drop;
			}
		}
	}

	QByteArray toByteArray() const
	{
		QByteArray data;
		QDataStream stream(&data,QIODevice::WriteOnly);
		EventType type=Drop;
		stream<<type<<drop;
		return data;
	}

	inline const QPoint &getDrop() const {return drop;}
	inline void setDrop(const QPoint &drop){this->drop=drop;}

	inline BitType getBit() const {return bit;}
	inline void setBit(BitType bit){this->bit=bit;}
};

#endif // SETEVENT_H
