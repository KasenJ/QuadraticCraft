#include "Handler.h"

void Handler::PlayerEventHandle(const PlayerEvent &event,const QHostAddress &address)
{
	qDebug()<<"Get PlayerEvent";
	QSqlQuery query;
	bool flag;
	query.prepare("SELECT Type FROM Cube WHERE Position=? AND Type=?");
	query.addBindValue(Utils::toInt(event.getPosition()));
	query.addBindValue(1); //To do
	flag=query.exec();

	if(flag) qDebug()<<"Query Cube In PlayerEventHandle Successed";
	else qDebug()<<"Query Cube In PlayerEventHandle Failed";
	if(query.first()){
		qDebug()<<"Can Move To This Position";
		query.prepare("UPDATE Player SET Position=? WHERE PName=?");
		query.addBindValue(Utils::toInt(event.getPosition()));
		query.addBindValue(userMap[address]);
		flag=query.exec();

		if(flag) qDebug()<<"Update Player In PlayerEventHandle Successed";
		else qDebug()<<"Update Player In PlayerEventHandle Failed";
	}
	else qDebug()<<"Can Not Move To This Position";

	foreach(auto it,event.getPackage()){
		query.prepare("SELECT Number FROM Cell WHERE PName=? AND Item=?");
		query.addBindValue(userMap[address]);
		query.addBindValue(it.first);
		flag=query.exec();

		if(flag) qDebug()<<"Query Cell For Item "<<it.first<<"In PlayerEventHandle Successed";
		else qDebug()<<"Query Cell For Item "<<it.first<<"In PlayerEventHandle Failed";
		if(query.first()){
			qDebug()<<"Find Item "<<it.first<<" In The Cell Then Update Cell";
			int number=query.record().value("Number").toInt();
			if(number+it.second>=0){
				qDebug()<<"Update Valid";
				query.prepare("UPDATE Cell SET Number=? WHERE WHERE PName=? AND Item=?");
				query.addBindValue(number+it.second);
				query.addBindValue(userMap[address]);
				query.addBindValue(it.first);
				flag=query.exec();
				if(flag) qDebug()<<"Update Cell For Item "<<it.first<<"In PlayerEventHandle Successed";
				else qDebug()<<"Update Cell For Item "<<it.first<<"In PlayerEventHandle Failed";
			}
			else qDebug()<<"Update Invalid";
		}
		else{
			qDebug()<<"Do Not Find Item "<<it.first<<" In The Cell The Insert Into Cell";
			if(it.second>=0){
				qDebug()<<"Insert Valid";
				query.prepare("INSERT INTO Cell (PName,Item,Number)""VALUES(?,?,?)");
				query.addBindValue(userMap[address]);
				query.addBindValue(it.first);
				query.addBindValue(it.second);
				flag=query.exec();
				if(flag) qDebug()<<"Insert Into Cell For Item "<<it.first<<"In PlayerEventHandle Successed";
				else qDebug()<<"Insert Into Cell For Item "<<it.first<<"In PlayerEventHandle Failed";
			}
			else qDebug()<<"Insert Invalid";
		}
	}
}
