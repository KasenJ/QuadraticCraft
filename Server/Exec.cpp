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
		emit(dataReceived(data,address));
	}
}

void Exec::writeData(const QByteArray &data,const QHostAddress &address)
{
	socket.writeDatagram(data,data.size(),address,port);
}
