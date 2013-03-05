#include "MoveEvent.h"

MoveEvent::MoveEvent(const QByteArray &data)
{
	if(!data.isEmpty()){
		QDataStream stream(data);
		quint8 type;
		stream>>type;
		if(type==Move){
			stream>>from>>to;
		}
	}
}

QByteArray MoveEvent::toByteArray()
{
	QByteArray data;
	QDataStream stream(data);
	quint8 type=Move;
	stream<<type<<from<<to;
	return data;
}

const QPoint &MoveEvent::fromPos()
{
	return from;
}

const QPoint &MoveEvent::toPos()
{
	return to;
}
