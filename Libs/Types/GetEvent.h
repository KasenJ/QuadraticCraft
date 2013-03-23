#ifndef GETEVENT_H
#define GETEVENT_H

#include <QPoint>
#include <QByteArray>
#include <QDataStream>
#include "Bit.h"
#include "Event.h"

class GetEvent:public Event
{
private:
	QPoint get;
	BitType bit;

public:
	GetEvent(const QByteArray &data=QByteArray())
	{
		if(!data.isEmpty()){
			QDataStream stream(data);
			EventType type;
			stream>>type;
			if(type==Get){
				stream>>get;
			}
		}
	}

	QByteArray toByteArray() const
	{
		QByteArray data;
		QDataStream stream(&data,QIODevice::WriteOnly);
		EventType type=Get;
		stream<<type<<get;
		return data;
	}

	inline const QPoint &getGet() const {return get;}
	inline void setGet(const QPoint &get){this->get=get;}

	inline BitType getBit() const {return bit;}
	inline void setBit(BitType bit){this->bit=bit;}
};

#endif // GETEVENT_H
