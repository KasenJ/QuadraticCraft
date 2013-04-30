#include "Handler.h"

void Handler::GetEventHandle(const GetEvent &event,const QHostAddress &address)
{
	qDebug()<<"Get GetEvent";
	QSqlQuery query;
	query.prepare("SELECT Type FROM Cube Where Position=?");
	query.addBindValue(Utils::toInt(event.getGet()));
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
		Package change={(QPair<BitType,qint8>(event.getBit(),1))};
		reply.setPackege(change);
		sendEvent(reply,address);

		query.prepare("UPDATE Cube SET Type=? Where Position=?");
		query.addBindValue(type>>8);
		query.addBindValue(Utils::toInt(event.getGet()));
		query.exec();
	}
	else qDebug()<<"No such item in Cube";
}
