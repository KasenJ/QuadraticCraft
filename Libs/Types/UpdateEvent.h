#ifndef UPDATEEVENT_H
#define UPDATEEVENT_H

#include <QRect>
#include <QVector>
#include <QByteArray>
#include <QDataStream>
#include "Bit.h"
#include "Event.h"

typedef QPair<BitType,QPoint> Role;

class UpdateEvent:public Event
{
private:
	QList<Role> roles;
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
				stream>>roles>>rects>>bitmap;
			}
		}
	}

	QByteArray toByteArray() const
	{
		QByteArray data;
		QDataStream stream(&data,QIODevice::WriteOnly);
		EventType type=Update;
		stream<<type<<roles<<rects<<bitmap;
		return data;
	}

	inline const QList<Role> &getRoles() const {return roles;}
	inline void setRoles(QList<Role> &roles){this->roles=roles;}

	inline const QList<QRect> &getRects() const {return rects;}
	inline void setRect(const QRect &rect){rects.clear();rects.append(rect);}
	inline void setRects(const QList<QRect> &rects){this->rects=rects;}

	inline const QVector<BitType> &getBitmap() const {return bitmap;}
	inline void setBitmap(const QVector<BitType> &bitmap){this->bitmap=bitmap;}

};

#endif // UPDATEEVENT_H
