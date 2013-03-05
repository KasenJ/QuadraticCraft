#include "UpdateEvent.h"

UpdateEvent::UpdateEvent(const QByteArray &data)
{
	if(!data.isEmpty()){
		QDataStream stream(data);
		quint8 type;
		stream>>type;
		if(type==Update){
			stream>>rect;
		}
	}
}

QByteArray UpdateEvent::toByteArray()
{
	QByteArray data;
	QDataStream stream(data);
	quint8 type=Update;
	stream<<type<<rect;
	return data;
}

const QRect &UpdateEvent::updateRect()
{
	return rect;
}
