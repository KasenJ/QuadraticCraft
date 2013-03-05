#ifndef GETEVENT_H
#define GETEVENT_H

#include <QPoint>
#include <QByteArray>
#include <QDataStream>
#include "Event.h"

class GetEvent:public Event
{
private:
	QPoint get;

public:
	GetEvent(const QByteArray &data=QByteArray());
	QByteArray toByteArray();
	inline const QPoint &getPos();
};

#endif // GETEVENT_H
