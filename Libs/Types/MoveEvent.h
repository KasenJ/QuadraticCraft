#ifndef MOVEEVENT_H
#define MOVEEVENT_H

#include <QPoint>
#include <QByteArray>
#include <QDataStream>
#include "Event.h"

class MoveEvent:public Event
{
private:
	QPoint to;

public:
	MoveEvent(const QByteArray &data=QByteArray())
	{
		if(!data.isEmpty()){
			QDataStream stream(data);
			EventType type;
			stream>>type;
			if(type==Move){
				stream>>to;
			}
		}
	}

	QByteArray toByteArray() const
	{
		QByteArray data;
		QDataStream stream(&data,QIODevice::WriteOnly);
		EventType type=Move;
		stream<<type<<to;
		return data;
	}

	inline const QPoint &getTo() const {return to;}
	inline void setTo(const QPoint &to){this->to=to;}
};

#endif // MOVEEVENT_H
