#ifndef DATAEVENT_H
#define DATAEVENT_H

#include <QList>
#include <QPixmap>
#include <QByteArray>
#include <QDataStream>
#include "Event.h"

class DataEvent:public Event
{
private:
	QHash<QString,QByteArray> data;

public:
	DataEvent(const QByteArray &_data=QByteArray())
	{
		if(!_data.isEmpty()){
			QDataStream stream(_data);
			EventType type;
			stream>>type;
			if(type==Data){
				stream>>data;
			}
		}
	}

	QByteArray toByteArray() const
	{
		QByteArray _data;
		QDataStream stream(&_data,QIODevice::WriteOnly);
		EventType type=Data;
		stream<<type<<data;
		return _data;
	}

	inline const QHash<QString,QByteArray> &getData() const {return data;}
	inline void setData(const QHash<QString,QByteArray> &data){this->data=data;}
};

#endif // DATAEVENT_H
