#ifndef SOCKET_H
#define SOCKET_H

#include <QtCore>
#include <QtNetwork>
#include "Event.h"
#include "DropEvent.h"
#include "GetEvent.h"
#include "MoveEvent.h"
#include "UpdateEvent.h"
#include "UserEvent.h"

typedef quint16 Port;

class Socket:public QUdpSocket
{
	Q_OBJECT
public:
	explicit Socket(QObject *parent=0);
	inline void setSendPort(Port port){send=port;}
	inline void setReceivePort(Port port){bind(port);}

private:
	Port send;

signals:
	void getDropEvent(const DropEvent &event,const QHostAddress &address);
	void getGetEvent(const GetEvent &event,const QHostAddress &address);
	void getMoveEvent(const MoveEvent &event,const QHostAddress &address);
	void getUpdateEvent(const UpdateEvent &event,const QHostAddress &address);
	void getUserEvent(const UserEvent &event,const QHostAddress &address);

public slots:
	void sendEvent(const Event &event,const QHostAddress &address);

private slots:
	void readData();
};

#endif // SOCKET_H
