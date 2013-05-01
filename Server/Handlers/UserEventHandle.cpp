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
			query.prepare("SELECT Position,Occupation FROM Player WHERE PName=?");
			query.addBindValue(userMap[address]);
			query.exec();
			if(query.first()){
				QPoint initPoint=Utils::toPoint(query.value("Position").toInt());

				PlayerEvent initPlayer;
				initPlayer.setName(userMap[address]);
				initPlayer.setOccupation(query.value("Occupation").toString());
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
				initPlayer.setName(userMap[address]);
				sendEvent(initPlayer,address);

				UpdateEvent initUpdate;
				QRect initRect(0,0,16,12);
				initRect.moveCenter(initPoint);
				int x=initRect.x(),y=initRect.y(),w=16,h=12;
				QVector<BitType> initBitmap(w*h,Bit::Black);
				for(int i=0;i<w;i++){
					query.prepare("SELECT Type,Position FROM Cube WHERE Position>=? AND Position<?");
					query.addBindValue(Utils::toInt(QPoint(x+i,y)));
					query.addBindValue(Utils::toInt(QPoint(x+i,y+h)));
					query.exec();
					while(query.next()){
						QPoint point=Utils::toPoint(query.value("Position").toInt());
						initBitmap[(point.y()-y)*w+point.x()-x]=query.value("Type").toInt();
					}
				}
				QList<QRect> initRects={initRect};
				initUpdate.setRects(initRects);
				initUpdate.setBitmap(initBitmap);
				sendEvent(initUpdate,address);
			}
		}
		else{
			qDebug()<<"User"<<event.getUsername()<<"Failed";
		}
		sendEvent(reply,address);
	}
	}
}
