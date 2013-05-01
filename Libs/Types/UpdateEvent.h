#ifndef UPDATEEVENT_H
#define UPDATEEVENT_H

#include <QRect>
#include <QVector>
#include <QByteArray>
#include <QDataStream>
#include "Bit.h"
#include "Event.h"

class UpdateEvent:public Event
{
private:
	QList<QRect> rects;
	QVector<BitType> bitmap;

public:
	UpdateEvent(const QByteArray &data=QByteArray())
	{
		if(!data.isEmpty()){
			QDataStream stream(data);
			EventType type;
			stream>>type;
			if(type==Update){
				stream>>rects>>bitmap;
			}
		}
	}

	QByteArray toByteArray() const
	{
		QByteArray data;
		QDataStream stream(&data,QIODevice::WriteOnly);
		EventType type=Update;
		stream<<type<<rects<<bitmap;
		return data;
	}

	inline const QList<QRect> &getRects() const {return rects;}
	inline void setRects(const QList<QRect> &rects){this->rects=rects;}

	inline const QVector<BitType> &getBitmap() const {return bitmap;}
	inline void setBitmap(const QVector<BitType> &bitmap){this->bitmap=bitmap;}

	inline bool isEmpty() const {return bitmap.isEmpty();}
};

#endif // UPDATEEVENT_H
