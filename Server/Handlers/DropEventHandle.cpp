#include "Handler.h"

void Handler::DropEventHandle(const DropEvent &event,const QHostAddress &address)
{
	qDebug()<<"Get DropEvent";
	QSqlQuery query;
	query.prepare("SELECT Number FROM Cell WHERE PName=? AND Item=? AND Number>0");
	query.addBindValue(userMap[address]);
	query.addBindValue(event.getBit());
	query.exec();
	if(query.first()){
		int number=query.value("Number").toInt()-1;
		query.prepare("SELECT Type FROM Cube WHERE POSITION=?");
		query.bindValue(0,Utils::toInt(event.getDrop()));
		query.exec();
		if(query.first()){
			query.prepare("UPDATE Cell SET Number=? WHERE PName=? AND Item=? AND Number>0");
			query.bindValue(0,number);
			query.bindValue(1,userMap[address]);
			query.bindValue(2,event.getBit());
			query.exec();

			query.prepare("UPDATE Cube SET TYPE=? WHERE POSITION=?");
			query.bindValue(0,event.getBit());
			query.bindValue(1,Utils::toInt(event.getDrop()));
			query.exec();

			PlayerEvent reply;
			Package change={(QPair<BitType,qint8>(event.getBit(),-1))};
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
