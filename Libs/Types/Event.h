#ifndef EVENT_H
#define EVENT_H

#include <QByteArray>
#include <QDataStream>

typedef quint8 EventType;

class Event
{
public:
	enum{Item,Player,Script,Update,User,Data};

	virtual QByteArray toByteArray() const=0;

	static EventType getType(const QByteArray &data)
	{
		EventType type;
		QDataStream stream(data);
		stream>>type;
		return type;
	}
};

#endif // EVENT_H
