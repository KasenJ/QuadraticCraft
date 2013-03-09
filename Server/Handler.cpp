#include "Handler.h"

Handler::Handler(QObject *parent):
	QObject(parent)
{
}

void Handler::setSocket(Socket *socket)
{
	this->socket=socket;
	connect(socket,&Socket::getDropEvent,this,&Handler::DropEventHandle);
	connect(socket,&Socket::getGetEvent,this,&Handler::GetEventHandle);
	connect(socket,&Socket::getMoveEvent,this,&Handler::MoveEventHandle);
	connect(socket,&Socket::getUpdateEvent,this,&Handler::UpdateEventHandle);
	connect(socket,&Socket::getUserEvent,this,&Handler::UserEventHandle);
}
