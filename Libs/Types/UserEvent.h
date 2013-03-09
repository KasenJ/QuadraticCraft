#ifndef USEREVENT_H
#define USEREVENT_H

#include <QString>
#include <QByteArray>
#include <QDataStream>
#include "Event.h"

typedef quint8 UserState;

class UserEvent:public Event
{
private:
	UserState state;
	QString username;
	QString password;

public:
	enum{Login,Logged,Failed,Logout,Modify};

	UserEvent(const QByteArray &data=QByteArray())
	{
		if(!data.isEmpty()){
			QDataStream stream(data);
			EventType type;
			stream>>type;
			if(type==User){
				stream>>state>>username>>password;
			}
		}
	}

	QByteArray toByteArray() const
	{
		QByteArray data;
		QDataStream stream(&data,QIODevice::WriteOnly);
		EventType type=User;
		stream<<type<<state<<username<<password;
		return data;
	}

	inline const UserState &getState() const {return state;}
	inline void setState(const UserState &state){this->state=state;}

	inline const QString &getUsername() const {return username;}
	inline void setUsername(const QString &username){this->username=username;}

	inline const QString &getPassword() const {return password;}
	inline void setPassword(const QString &password){this->password=password;}
};

#endif // USEREVENT_H
