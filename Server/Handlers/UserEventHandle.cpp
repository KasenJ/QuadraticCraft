#include "Handler.h"

void Handler::UserEventHandle(const UserEvent &event,const QHostAddress &address)
{
	qDebug()<<"Get UserEvent";
	UserEvent reply;
	switch(event.getState())
	{
	case UserEvent::Login:
	{
		QSqlQuery query;
		query.prepare("SELECT * FROM Player WHERE PName=?");
		query.addBindValue(event.getUsername());
		query.exec();
		if(query.first()){
			if(query.value("Password").toString()==event.getPassword()){
				reply.setState(UserEvent::Logged);
			}
			else{
				qDebug()<<"Wrong Password";
				reply.setState(UserEvent::Failed);
			}
		}
		else{
			qDebug()<<"Init Player Info";
			query.prepare("INSERT INTO Player VALUES (?,?,?)");
			query.addBindValue(event.getUsername());
			query.addBindValue("Undefined");
			query.addBindValue(event.getPassword());
			if(query.exec()){
				qDebug()<<"Init Succeed";
				reply.setState(UserEvent::Logged);
			}
			else{
				qDebug()<<"Init Failed";
				reply.setState(UserEvent::Failed);
			}
		}
		if(reply.getState()==UserEvent::Logged){
			userMap[address]=query.value("PName").toString();
			qDebug()<<"User"<<event.getUsername()<<"Logged";
		}
		else{
			qDebug()<<"User"<<event.getUsername()<<"Failed";
		}
		sendEvent(reply,address);
	}
	}
}
