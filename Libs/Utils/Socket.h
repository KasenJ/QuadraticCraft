#ifndef SOCKET_H
#define SOCKET_H

#include <QtCore>
#include <QtNetwork>
#include "Types.h"

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
	void getItemEvent(const ItemEvent &event,const QHostAddress &address);
	void getPlayerEvent(const PlayerEvent &event,const QHostAddress &address);
	void getUpdateEvent(const UpdateEvent &event,const QHostAddress &address);
	void getUserEvent(const UserEvent &event,const QHostAddress &address);

public slots:
	void sendEvent(const Event &event,const QHostAddress &address);

private slots:
	void readData();
};

#endif // SOCKET_H
