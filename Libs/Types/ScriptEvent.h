#ifndef SCRIPTEVENT_H
#define SCRIPTEVENT_H

#include <QList>
#include <QLine>
#include <QString>
#include "Event.h"

typedef QList<QPair<QLine,quint32> > Track;
typedef QList<QPair<QString,quint32> > Dialog;

class ScriptEvent:public Event
{
private:
	Track motion;
	Dialog dialog;

public:
	ScriptEvent(const QByteArray &data=QByteArray())
	{
		if(!data.isEmpty()){
			QDataStream stream(data);
			EventType type;
			stream>>type;
			if(type==Script){
				stream>>motion>>dialog;
			}
		}
	}

	QByteArray toByteArray() const
	{
		QByteArray data;
		QDataStream stream(&data,QIODevice::WriteOnly);
		EventType type=Script;
		stream<<type<<motion<<dialog;
		return data;
	}

	inline const Track &getMotion() const {return motion;}
	inline void setMotion(const Track &_motion){motion=_motion;}

	inline const Dialog &getDialog() const {return dialog;}
	inline void setDialog(const Dialog &_dialog){dialog=_dialog;}
};

#endif // SCRIPTEVENT_H
