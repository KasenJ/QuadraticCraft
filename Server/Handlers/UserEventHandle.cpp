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
			bool flag=false;
			query.prepare("SELECT Data FROM Info WHERE Name=?");
			query.addBindValue("Rect");
			query.exec();
			if(query.first()){
				QRect w=Utils::fromByteArray<QRect>(query.value("Data").toByteArray());
				qsrand(QTime::currentTime().msec());
				int p;
				bool c=true;
				while(c){
					p=Utils::toInt(w.topLeft()+QPoint(qrand()%w.width(),qrand()%w.height()));
					query.prepare("SELECT Move FROM Cube,Bit WHERE Position=? AND Cube.Type%256=Bit.Type");
					query.addBindValue(p);
					query.exec();
					c=!query.first();
				}
				query.prepare("INSERT INTO Player VALUES (?,?,?,?)");
				query.addBindValue(event.getUsername());
				query.addBindValue(event.getPassword());
				query.addBindValue(128);
				query.addBindValue(p);
				if(query.exec()){
					qDebug()<<"Init Succeed";
					reply.setState(UserEvent::Logged);
					flag=true;
				}
			}
			if(!flag){
				qDebug()<<"Init Failed";
				reply.setState(UserEvent::Failed);
			}
		}
		if(reply.getState()==UserEvent::Logged){
			userMap[address]=event.getUsername();
			qDebug()<<"User"<<userMap[address]<<"Logged";
			query.prepare("SELECT Player.Position,Bit.Info FROM Player,Bit WHERE PName=? AND Player.Occupation=Bit.Type");
			query.addBindValue(userMap[address]);
			query.exec();
			if(query.first()){
				QPoint initPoint=Utils::toPoint(query.value("Position").toInt());
				QString n;
				QDataStream s(query.value("Info").toByteArray());
				s>>n;
				PlayerEvent initPlayer;
				initPlayer.setName(userMap[address]);
				initPlayer.setOccupation(n);
				initPlayer.setPosition(initPoint);
				query.prepare("SELECT Item,Number FROM Cell WHERE PName=?");
				query.addBindValue(userMap[address]);
				query.exec();
				Package initPackage;
				while(query.next()){
					Cell cell(query.value("Item").toInt(),query.value("Number").toInt());
					initPackage.append(cell);
				}
				initPlayer.setPackege(initPackage);
				initPlayer.setName(userMap[address]);

				UpdateEvent initUpdate;
				QList<Role> initRoles;
				query.prepare("SELECT Occupation,Position FROM Player;");
				query.exec();
				while(query.next()){
					auto b=query.value("Occupation").toInt();
					auto p=Utils::toPoint(query.value("Position").toInt());
					initRoles.append(Role(b,p));
				}
				initUpdate.setRoles(initRoles);

				Utils::delayExec(0,[=](){
					sendEvent(initPlayer,address);
					sendEvent(initUpdate,address);
				});
			}
		}
		else{
			qDebug()<<"User"<<event.getUsername()<<"Failed";
		}
		sendEvent(reply,address);
		break;
	}
	case UserEvent::Logout:
	{
		userMap.remove(address);
		qDebug()<<"User"<<event.getUsername()<<"Logout";
		break;
	}
	}
}
