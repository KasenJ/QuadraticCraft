#include "Handler.h"

void Handler::DropEventHandle(const DropEvent &event,const QHostAddress &address)
{
	qDebug()<<"Get DropEvent";
	QSqlQuery query;
	bool flag;
	query.prepare("SELECT Number FROM Cell WHERE PName=? AND Item=? AND Number>0");
	query.addBindValue(userMap[address]);
	query.addBindValue(event.getBit());
	flag=query.exec();

	if(flag) qDebug()<<"Query Cell In The DropEventHandler Successed";
	else qDebug()<<"Query Cell In The DropEventHandler Failed";

	if(query.first()){
		qDebug()<<"Find Such Item In Package";
		int number=query.value("Number").toInt()-1;
		query.prepare("SELECT Type FROM Cube WHERE POSITION=?");
		query.bindValue(0,Utils::toInt(event.getDrop()));
		flag=query.exec();

		if(flag) qDebug()<<"Query Cube In The DropEventHandler Successed";
		else qDebug()<<"Query Cube In The DropEventHandler Failed";
		if(query.first()){
			qDebug()<<"Drop To Do";
			query.prepare("UPDATE Cell SET Number=? WHERE PName=? AND Item=? AND Number>0");
			query.bindValue(0,number);
			query.bindValue(1,userMap[address]);
			query.bindValue(2,event.getBit());
			flag=query.exec();

			if(flag) qDebug()<<"Update Package In The DropEventHandler Successed";
			else qDebug()<<"Update Package In The DropEventHandler Failed";
			query.prepare("UPDATE Cube SET TYPE=? WHERE POSITION=?");
			query.bindValue(0,event.getBit());
			query.bindValue(1,Utils::toInt(event.getDrop()));
			flag=query.exec();

			if(flag) qDebug()<<"Update Cube In The DropEventHandler Successed";
			else qDebug()<<"Update Cube In The DropEventHandler Failed";
		}
		else qDebug()<<"No Space To Drop";
	}
	else qDebug()<<"No Such Item In Package";
}
