#include "Handler.h"

void Handler::GetEventHandle(const GetEvent &event,const QHostAddress &address)
{
	qDebug()<<"Get GetEvent";
	QSqlQuery query;
	bool flag;
	query.prepare("SELECT Type FROM Cube Where Position=?");
	query.addBindValue(Utils::toInt(event.getGet()));
	flag=query.exec();

	if(flag) qDebug()<<"Query Cube In The GetEventHandler Successed";
	else qDebug()<<"Query Cube In The GetEventHandler Failed";
	if(query.first()){
		qDebug()<<"Find Suce Item In Cube";
		int type=query.record().value("Type").toInt();
		query.prepare("SELECT * FROM Cell WHERE PName=? AND Item=?");
		query.addBindValue(userMap[address]);
		query.addBindValue(type);
		flag=query.exec();

		if(flag) qDebug()<<"Query Cell In The GetEventHandler Successed";
		else qDebug()<<"Query Cell In The GetEventHandler Failed";
		if(query.first()){
			int number=query.record().value("Number").toInt();
			query.prepare("UPDATE Cell SET Number=? WHERE PName=? AND Item=?");
			query.addBindValue(++number);
			query.addBindValue(userMap[address]);
			query.addBindValue(type);
			flag=query.exec();
		}
		else{
			query.prepare("INSERT INTO Cell (PName,Item,Number)""VALUES(?,?,?)");
			query.addBindValue(userMap[address]);
			query.addBindValue(type);
			query.addBindValue(1);
			flag=query.exec();
		}

		if(flag) qDebug()<<"Update Cell In The GetEventHandler Successed";
		else qDebug()<<"Update Cell In The GetEventHandler Failed";
		query.prepare("UPDATE Cube SET Type=? Where Position=?");
		query.addBindValue(type>>8);
		query.addBindValue(Utils::toInt(event.getGet()));
		flag=query.exec();

		if(flag) qDebug()<<"Update Cube In The GetEventHandler Successed";
		else qDebug()<<"Update Cube In The GetEventHandler Failed";
	}
	else qDebug()<<"No such item in Cube";
}
