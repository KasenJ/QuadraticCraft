#include "Handler.h"

void Handler::ItemEventHandle(const ItemEvent &event,const QHostAddress &address)
{
	qDebug()<<"Get ItemEvent";
	switch(event.getOperation())
	{
	case ItemEvent::Get:
	{
		QSqlQuery query;
		query.prepare("SELECT Type FROM Cube Where Position=?");
		query.addBindValue(Utils::toInt(event.getPoint()));
		query.exec();
		if(query.first()){
			int type=query.value("Type").toInt();
			query.prepare("SELECT * FROM Cell WHERE PName=? AND Item=?");
			query.addBindValue(userMap[address]);
			query.addBindValue(type);
			query.exec();
			if(query.first()){
				int number=query.value("Number").toInt();
				query.prepare("UPDATE Cell SET Number=? WHERE PName=? AND Item=?");
				query.addBindValue(++number);
				query.addBindValue(userMap[address]);
				query.addBindValue(type);
			}
			else{
				query.prepare("INSERT INTO Cell (PName,Item,Number)""VALUES(?,?,?)");
				query.addBindValue(userMap[address]);
				query.addBindValue(type);
				query.addBindValue(1);
			}
			query.exec();
			PlayerEvent reply;
			Package change={(QPair<BitType,qint8>(type,1))};
			reply.setPackege(change);
			sendEvent(reply,address);

			query.prepare("UPDATE Cube SET Type=? Where Position=?");
			query.addBindValue(type>>8);
			query.addBindValue(Utils::toInt(event.getPoint()));
			query.exec();
		}
		else qDebug()<<"No such item in Cube";
	}
	case ItemEvent::Drop:
	{
		QSqlQuery query;
		query.prepare("SELECT Number FROM Cell WHERE PName=? AND Item=? AND Number>0");
		BitType type=event.getPackage().first().first;
		query.addBindValue(userMap[address]);
		query.addBindValue(type);
		query.exec();
		if(query.first()){
			int number=query.value("Number").toInt()-1;
			query.prepare("SELECT Type FROM Cube WHERE POSITION=?");
			query.bindValue(0,Utils::toInt(event.getPoint()));
			query.exec();
			if(query.first()){
				query.prepare("UPDATE Cell SET Number=? WHERE PName=? AND Item=? AND Number>0");
				query.bindValue(0,number);
				query.bindValue(1,userMap[address]);
				query.bindValue(2,type);
				query.exec();

				query.prepare("UPDATE Cube SET TYPE=? WHERE POSITION=?");
				query.bindValue(0,event.getPoint());
				query.bindValue(1,Utils::toInt(event.getPoint()));
				query.exec();

				PlayerEvent reply;
				Package change={(QPair<BitType,qint8>(type,-1))};
				reply.setPackege(change);
				sendEvent(reply,address);
			}
			else{
				qDebug()<<"No Space To Drop";
			}
		}
		else{
			qDebug()<<"No Such Item In Package";
		}
	}
	}
}
