#include "SetEvent.h"

SetEvent::SetEvent(const QByteArray &data)
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

QByteArray SetEvent::toByteArray()
{
	QByteArray data;
	QDataStream stream(data);
	quint8 type=Set;
	stream<<type<<set;
	return data;
}

const QPoint &SetEvent::setPos()
{
	return set;
}
