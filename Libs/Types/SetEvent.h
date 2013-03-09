#ifndef SETEVENT_H
#define SETEVENT_H

#include <QPoint>
#include <QByteArray>
#include <QDataStream>
#include "Event.h"

class SetEvent:public Event
{
private:
	QPoint set;
	quint8 bit;

public:
	SetEvent(const QByteArray &data=QByteArray())
	{
		if(!data.isEmpty()){
			QDataStream stream(data);
			quint8 type;
			stream>>type;
			if(type==Set){
				stream>>set;
			}
		}
	}

	QByteArray toByteArray()
	{
		QByteArray data;
		QDataStream stream(&data,QIODevice::WriteOnly);
		quint8 type=Set;
		stream<<type<<set;
		return data;
	}

	inline const QPoint &getSet(){return set;}
	inline void setSet(const QPoint &set){this->set=set;}

	inline quint8 getBit(){return bit;}
	inline void setBit(quint8 bit){this->bit=bit;}
};

#endif // SETEVENT_H
