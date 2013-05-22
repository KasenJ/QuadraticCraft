#include "Handler.h"

Handler::Handler(QObject *parent):
	QObject(parent)
{
	data=QSqlDatabase::addDatabase("QSQLITE");
	data.setDatabaseName("Data.db");
	data.open();
	QSqlQuery().exec("PRAGMA synchronous = OFF;");
}

Handler::~Handler()
{
	data.close();
}

void Handler::setSocket(Socket *socket)
{
	this->socket=socket;
	connect(socket,&Socket::getItemEvent,this,&Handler::ItemEventHandle);
	connect(socket,&Socket::getPlayerEvent,this,&Handler::PlayerEventHandle);
	connect(socket,&Socket::getUpdateEvent,this,&Handler::UpdateEventHandle);
	connect(socket,&Socket::getUserEvent,this,&Handler::UserEventHandle);
}
