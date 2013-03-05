#include "GetEvent.h"

GetEvent::GetEvent(const QByteArray &data)
{
	if(!data.isEmpty()){
		QDataStream stream(data);
		quint8 type;
		stream>>type;
		if(type==Get){
			stream>>get;
		}
	}
}

QByteArray GetEvent::toByteArray()
{
	QByteArray data;
	QDataStream stream(data);
	quint8 type=Get;
	stream<<type<<get;
	return data;
}

const QPoint &GetEvent::getPos()
{
	return get;
}
