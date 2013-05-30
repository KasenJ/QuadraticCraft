#ifndef ITEMEVENT_H
#define ITEMEVENT_H

#include <QPoint>
#include <QByteArray>
#include <QDataStream>
#include "Bit.h"
#include "Event.h"

typedef quint8 Operation;
typedef QPair<BitType,qint8> Cell;
typedef QList<Cell> Package;

class ItemEvent:public Event
{
private:
	QPoint point;
	Package package;
	Operation operation;

public:
	enum{Get,Drop,Produce};

	ItemEvent(const QByteArray &data=QByteArray())
	{
		if(!data.isEmpty()){
			QDataStream stream(data);
			EventType type;
			stream>>type;
			if(type==Item){
				stream>>point>>package>>operation;
			}
		}
	}

	QByteArray toByteArray() const
	{
		QByteArray data;
		QDataStream stream(&data,QIODevice::WriteOnly);
		EventType type=Item;
		stream<<type<<point<<package<<operation;
		return data;
	}
	inline const QPoint &getPoint() const {return point;}
	inline void setPoint(const QPoint &point){this->point=point;}

	inline const Package &getPackage() const {return package;}
	inline void setPackege(const Package &package){this->package=package;}

	inline Operation getOperation() const {return operation;}
	inline void setOperation(Operation operation){this->operation=operation;}
};

#endif // ITEMEVENT_H
