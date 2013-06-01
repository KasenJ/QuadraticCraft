#ifndef UPDATEEVENT_H
#define UPDATEEVENT_H

#include <QRect>
#include <QVector>
#include <QByteArray>
#include <QDataStream>
#include "Event.h"

typedef quint8 BitType;
typedef quint64 SquareType;
typedef QVector<SquareType> Bitmap;
typedef QPair<BitType,QPoint> Role;

class UpdateEvent:public Event
{
private:
	QList<Role> roles;
	QList<QRect> rects;
	QVector<SquareType> bitmap;

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

	inline const Bitmap &getBitmap() const {return bitmap;}
	inline void setBitmap(const Bitmap &bitmap){this->bitmap=bitmap;}

};

#endif // UPDATEEVENT_H
