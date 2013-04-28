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
		query.prepare("SELECT Password FROM Player WHERE PName=?");
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
			query.prepare("INSERT INTO Player VALUES (?,?,?,?,?)");
			query.addBindValue(event.getUsername());
			query.addBindValue("Undefined");
			query.addBindValue("Undefined");
			query.addBindValue(event.getPassword());
			query.addBindValue(qrand()%(0xFFFFFFFF>>1));
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
			userMap[address]=event.getUsername();
			qDebug()<<"User"<<userMap[address]<<"Logged";
			query.prepare("SELECT Position FROM Player WHERE PName=?");
			query.addBindValue(userMap[address]);
			query.exec();
			if(query.first()){
				UpdateEvent initUpdate;
				QRect initRect(0,0,16,12);
				QPoint initPoint=Utils::toPoint(query.value("Position").toInt());
				initRect.moveCenter(initPoint);
				initUpdate.setRect(initRect);
				UpdateEventHandle(initUpdate,address);
				PlayerEvent initPlayer;
				initPlayer.setPosition(initPoint);
				query.prepare("SELECT Item, Number FROM Cell WHERE PName=?");
				query.addBindValue(userMap[address]);
				query.exec();
				Package initPackage;
				while(query.next()){
					auto cell=qMakePair(query.value("Item").value<BitType>(),query.value("Number").value<qint8>());
					initPackage.append(cell);
				}
				initPlayer.setPackege(initPackage);
				socket->sendEvent(initPlayer,address);
			}
		}
		else{
			qDebug()<<"User"<<event.getUsername()<<"Failed";
		}
		sendEvent(reply,address);
	}
	}
}
