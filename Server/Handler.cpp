#include "Handler.h"

Handler::Handler(QObject *parent):
	QObject(parent)
{
	data=QSqlDatabase::addDatabase("QSQLITE");
	data.setDatabaseName("Data.db");
	data.open();
	QSqlQuery().exec("PRAGMA synchronous = OFF;");
	QSqlQuery().exec("PRAGMA foreign_keys = ON;");
	QSqlQuery query(data);
	query.exec("SELECT * FROM Access");
	while(query.next()) access.insert(query.value("Type").toInt(),query.value("Control").toBool());
	query.exec("SELECT * FROM Event");
	while(query.next()) events.append(QPair<QRect,ScriptEvent>(query.value("Rect").toRect(),query.value("Script").toByteArray()));
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
