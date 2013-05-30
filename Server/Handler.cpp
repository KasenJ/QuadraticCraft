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
	while(query.next()){
		const auto &t=query.value("Type").toInt();
		const auto &c=query.value("Control").toBool();
		access.insert(t,c);
	}
	query.exec("SELECT * FROM Event");
	while(query.next()){
		const auto &r=Utils::fromByteArray<QRect>(query.value("Rect").toByteArray());
		const auto &e=ScriptEvent(query.value("Script").toByteArray());
		events.append(qMakePair(r,e));
	}
}

Handler::~Handler()
{
	data.close();
}

void Handler::sendEvent(const Event &event,const QHostAddress &address)
{
	socket->sendEvent(event,address);
}

void Handler::broadEvent(const Event &event)
{
	for(const QHostAddress &user:userMap.keys()){
		sendEvent(event,user);
	}
}

void Handler::setSocket(Socket *socket)
{
	this->socket=socket;
	connect(socket,&Socket::getItemEvent,this,&Handler::ItemEventHandle);
	connect(socket,&Socket::getPlayerEvent,this,&Handler::PlayerEventHandle);
	connect(socket,&Socket::getUpdateEvent,this,&Handler::UpdateEventHandle);
	connect(socket,&Socket::getUserEvent,this,&Handler::UserEventHandle);
}
