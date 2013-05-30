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
		reach=access[type];
	}
	if(reach){
		for(auto iter=events.begin();iter!=events.end();){
			if(iter->first.contains(event.getPosition())){
				ScriptEvent replyScr=iter->second;
				query.prepare("DELETE FROM Event WHERE Rect=?");
				query.addBindValue(Utils::toByteArray(iter->first));
				query.exec();
				iter=events.erase(iter);
				sendEvent(replyScr,address);
			}
			else{
				++iter;
			}
		}
	}
	PlayerEvent reply;
	if(reach){
		query.prepare("UPDATE Player SET Position=? WHERE PName=?");
		query.addBindValue(Utils::toInt(event.getPosition()));
		query.addBindValue(userMap[address]);
		query.exec();
		reply.setPosition(event.getPosition());
		UpdateEvent update;
		QList<Role> roles;
		query.prepare("SELECT Occupation,Position FROM Player;");
		query.exec();
		while(query.next()){
			auto b=Bit::White;
			auto p=Utils::toPoint(query.value("Position").toInt());
			roles.append(Role(b,p));
		}
		update.setRoles(roles);
		for(QHostAddress a:userMap.keys()){
			sendEvent(update,a);
		}
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
			change.append(it);
		}
		else{
			qDebug()<<"Update Item"<<it.first<<"Failed";
		}
	}
	reply.setPackege(change);
	sendEvent(reply,address);
}
