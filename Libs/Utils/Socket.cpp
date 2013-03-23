#include "Socket.h"

Socket::Socket(QObject *parent):
	QUdpSocket(parent)
{
	connect(this,&QUdpSocket::readyRead,this,&Socket::readData);
}

void Socket::readData()
{
	while(hasPendingDatagrams()){
		QByteArray data;
		data.resize(pendingDatagramSize());
		QHostAddress address;
		readDatagram(data.data(),data.size(),&address);
		switch(Event::getType(data)){
		case Event::Drop:{
			DropEvent event(data);
			emit getDropEvent(event,address);
			break;
		}
		case Event::Get:{
			GetEvent event(data);
			emit getGetEvent(event,address);
			break;
		}
		case Event::Player:{
			PlayerEvent event(data);
			emit getPlayerEvent(event,address);
			break;
		}
		case Event::Update:{
			UpdateEvent event(data);
			emit getUpdateEvent(event,address);
			break;
		}
		case Event::User:{
			UserEvent event(data);
			emit getUserEvent(event,address);
			break;
		}
		}
	}
}

void Socket::sendEvent(const Event &event,const QHostAddress &address)
{
	writeDatagram(event.toByteArray(),address,send);
}
