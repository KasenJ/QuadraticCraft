#ifndef HANDLER_H
#define HANDLER_H

#include <QtCore>
#include <QtNetwork>
#include "Types.h"

class Handler:public QObject
{
	Q_OBJECT
public:
	explicit Handler(QObject *parent=0);
	void setSocket(Socket *socket);

private:
	Socket *socket;
	inline void sendEvent(const Event &event,const QHostAddress &address){socket->sendEvent(event,address);}

public slots:
	void DropEventHandle(const DropEvent &event,const QHostAddress &address);
	void GetEventHandle(const GetEvent &event,const QHostAddress &address);
	void MoveEventHandle(const MoveEvent &event,const QHostAddress &address);
	void UpdateEventHandle(const UpdateEvent &event,const QHostAddress &address);
	void UserEventHandle(const UserEvent &event,const QHostAddress &address);
};

#endif // HANDLER_H
