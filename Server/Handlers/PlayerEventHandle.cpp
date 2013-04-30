#include "Handler.h"

void Handler::PlayerEventHandle(const PlayerEvent &event,const QHostAddress &address)
{
	qDebug()<<"Get PlayerEvent";
	QSqlQuery query;
	query.prepare("UPDATE Player SET Position=? WHERE PName=?");
	query.addBindValue(Utils::toInt(event.getPosition()));
	query.addBindValue(userMap[address]);
	query.exec();
	PlayerEvent reply;
	reply.setPosition(event.getPosition());
	socket->sendEvent(reply,address);
}
