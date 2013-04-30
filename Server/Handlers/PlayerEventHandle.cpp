#include "Handler.h"

void Handler::PlayerEventHandle(const PlayerEvent &event,const QHostAddress &address)
{
	qDebug()<<"Get PlayerEvent";
	QSqlQuery query;
	query.prepare("SELECT Type FROM Cube WHERE Position=?");
	query.addBindValue(Utils::toInt(event.getPosition()));
	query.exec();
	bool reach=query.first();
	if(reach){
		int type=query.value("Type").toInt();
		if(type==0){
			reach=false;
		}
	}
	PlayerEvent reply;
	if(reach){
		query.prepare("UPDATE Player SET Position=? WHERE PName=?");
		query.addBindValue(Utils::toInt(event.getPosition()));
		query.addBindValue(userMap[address]);
		query.exec();
		reply.setPosition(event.getPosition());
	}
	else{
		qDebug()<<"Can Not Move To This Position";
	}

	Package change;
	for(auto it:event.getPackage()){
		query.prepare("SELECT Number FROM Cell WHERE PName=? AND Item=?");
		query.addBindValue(userMap[address]);
		query.addBindValue(it.first);
		query.exec();
		bool flag=false;
		if(query.first()){
			int number=query.value("Number").toInt();
			if(number+it.second>=0){
				flag=true;
				query.prepare("UPDATE Cell SET Number=? WHERE WHERE PName=? AND Item=?");
				query.addBindValue(number+it.second);
				query.addBindValue(userMap[address]);
				query.addBindValue(it.first);
				query.exec();
			}
		}
		else if(it.second>=0){
			flag=true;
			query.prepare("INSERT INTO Cell VALUES(?,?,?)");
			query.addBindValue(userMap[address]);
			query.addBindValue(it.first);
			query.addBindValue(it.second);
			query.exec();
		}
		if(flag){
			qDebug()<<"Update Item"<<it.first<<"Succeed";
			change.append(it);
		}
		else{
			qDebug()<<"Update Item"<<it.first<<"Failed";
		}
	}
	reply.setPackege(change);
	sendEvent(reply,address);
}
