#ifndef UPDATEEVENT_H
#define UPDATEEVENT_H

#include <QRect>
#include <QByteArray>
#include <QDataStream>
#include "Event.h"

class UpdateEvent:public Event
{
private:
	QRect rect;

public:
	UpdateEvent(const QByteArray &data=QByteArray());
	QByteArray toByteArray();
	inline const QRect &updateRect();
};

#endif // UPDATEEVENT_H
