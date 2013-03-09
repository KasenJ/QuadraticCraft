#include "Exec.h"

Exec::Exec(QObject *parent):
	QObject(parent)
{
}

void Exec::bind(quint16 port)
{
	this->port=port;
	socket.bind(port);
	connect(&socket,&QUdpSocket::readyRead,this,&Exec::readData);
}

void Exec::readData()
{
	while(socket.hasPendingDatagrams()){
		QByteArray data;
		data.resize(socket.pendingDatagramSize());
		QHostAddress address;
		socket.readDatagram(data.data(),data.size(),&address);
		quint8 type=Event::getType(data);
		if(type==Event::Update){
			UpdateEvent event(data);
			const QRect rect=event.getRect();
			QList<quint8> bitmap;
			int n=rect.height()*rect.width();
			for(int i=0;i<n;i++){
				bitmap.append(0);
			}
			event.setBitmap(bitmap);
			writeData(event.toByteArray(),address);
		}
		if(type==Event::User){
			UserEvent event(data);
			event.setState(UserEvent::Logged);
			event.setUsername(QString());
			event.setPassword(QString());
			writeData(event.toByteArray(),address);
		}
	}
}

void Exec::writeData(const QByteArray &data,const QHostAddress &address)
{
	socket.writeDatagram(data,data.size(),address,port);
}
