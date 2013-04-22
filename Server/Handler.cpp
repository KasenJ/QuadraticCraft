#include "Handler.h"

Handler::Handler(QObject *parent):
	QObject(parent)
{
	data=QSqlDatabase::addDatabase("QSQLITE");
	data.setDatabaseName("Data.db");
	data.open();
}

Handler::~Handler()
{
	data.close();
}

void Handler::setSocket(Socket *socket)
{
	this->socket=socket;
	connect(socket,&Socket::getDropEvent,this,&Handler::DropEventHandle);
	connect(socket,&Socket::getGetEvent,this,&Handler::GetEventHandle);
	connect(socket,&Socket::getPlayerEvent,this,&Handler::PlayerEventHandle);
	connect(socket,&Socket::getUpdateEvent,this,&Handler::UpdateEventHandle);
	connect(socket,&Socket::getUserEvent,this,&Handler::UserEventHandle);
}
