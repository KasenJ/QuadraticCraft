#ifndef MOVEEVENT_H
#define MOVEEVENT_H

#include <QPoint>
#include <QByteArray>
#include <QDataStream>
#include "Event.h"

class MoveEvent:public Event
{
private:
	QPoint from;
	QPoint to;

public:
	MoveEvent(const QByteArray &data=QByteArray());
	QByteArray toByteArray();
	inline const QPoint &fromPos();
	inline const QPoint &toPos();
};

#endif // MOVEEVENT_H
