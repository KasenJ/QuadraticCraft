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
			bool flag=true;
			qDebug()<<"Init Player Info";
			query.prepare("INSERT INTO Player VALUES (?,?,?)");
			query.addBindValue(event.getUsername());
			query.addBindValue("Undefined");
			query.addBindValue(event.getPassword());
			flag=flag&&query.exec();
			qDebug()<<"Init Player Position";
			query.prepare("INSERT INTO At VALUES (?,?)");
			query.addBindValue(event.getUsername());
			query.addBindValue(qrand()%(0xFFFFFFFF>>1));
			flag=flag&&query.exec();
			if(flag){
				qDebug()<<"Init Succeed";
				reply.setState(UserEvent::Logged);
			}
			else{
				qDebug()<<"Init Failed";
				reply.setState(UserEvent::Failed);
			}
		}
		if(reply.getState()==UserEvent::Logged){
			userMap[address]=event.getUsername();
			qDebug()<<"User"<<userMap[address]<<"Logged";
			query.prepare("SELECT Position FROM At WHERE PName=?");
			query.addBindValue(userMap[address]);
			query.exec();
			if(query.first()){
				UpdateEvent initUpdate;
				QRect initRect(0,0,16,12);
				initRect.moveCenter(Utils::toPoint(query.value("Position").toInt()));
				initUpdate.setRect(initRect);
				UpdateEventHandle(initUpdate,address);
			}
		}
		else{
			qDebug()<<"User"<<event.getUsername()<<"Failed";
		}
		sendEvent(reply,address);
	}
	}
}
