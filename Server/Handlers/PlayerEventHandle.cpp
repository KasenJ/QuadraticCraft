#include "Handler.h"

void Handler::PlayerEventHandle(const PlayerEvent &event,const QHostAddress &address)
{
	qDebug()<<"Get PlayerEvent";
	QSqlQuery query;
	query.prepare("SELECT Type FROM Cube WHERE Position=?");
	query.addBindValue(Utils::toInt(event.getPosition()));
	query.exec();
	if(query.first()){
		query.prepare("UPDATE Player SET Position=? WHERE PName=?");
		query.addBindValue(Utils::toInt(event.getPosition()));
		query.addBindValue(userMap[address]);
		query.exec();
	}
	else{
		qDebug()<<"Can Not Move To This Position";
	}

	for(auto it:event.getPackage()){
		query.prepare("SELECT Number FROM Cell WHERE PName=? AND Item=?");
		query.addBindValue(userMap[address]);
		query.addBindValue(it.first);
		query.exec();
		if(query.first()){
			int number=query.record().value("Number").toInt();
			if(number+it.second>=0){
				qDebug()<<"Update Valid";
				query.prepare("UPDATE Cell SET Number=? WHERE WHERE PName=? AND Item=?");
				query.addBindValue(number+it.second);
				query.addBindValue(userMap[address]);
				query.addBindValue(it.first);
				query.exec();
			}
			else qDebug()<<"Update Invalid";
		}
		else{
			if(it.second>=0){
				qDebug()<<"Insert Valid";
				query.prepare("INSERT INTO Cell (PName,Item,Number)""VALUES(?,?,?)");
				query.addBindValue(userMap[address]);
				query.addBindValue(it.first);
				query.addBindValue(it.second);
				query.exec();
			}
			else qDebug()<<"Insert Invalid";
		}
	}
}
