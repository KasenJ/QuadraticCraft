#include "Event.h"

quint8 Event::getType(const QByteArray &data)
{
	quint8 type;
	QDataStream stream(data);
	stream>>type;
	return type;
}
