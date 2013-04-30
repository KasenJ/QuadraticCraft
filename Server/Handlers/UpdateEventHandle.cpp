#include "Handler.h"

void Handler::UpdateEventHandle(const UpdateEvent &event,const QHostAddress &address)
{
	qDebug()<<"Get UpdateEvent";
	QSqlQuery query;
	QRect rect=event.getRect();
	int x=rect.x(),y=rect.y(),w=rect.width(),h=rect.height();
	QVector<BitType> bitmap(w*h,Bit::Black);
	for(int i=0;i<w;i++){
		query.prepare("SELECT Type,Position FROM Cube WHERE Position>=? AND Position<=?");
		query.addBindValue(Utils::toInt(QPoint(x+i,y)));
		query.addBindValue(Utils::toInt(QPoint(x+i,y+h)));
		query.exec();
		while(query.next()){
			QPoint point=Utils::toPoint(query.value("Position").toInt());
			bitmap[point.x()*w+point.y()]=query.value("Type").toInt();
		}
	}
	UpdateEvent reply;
	reply.setRect(rect);
	reply.setBitmap(bitmap);
	sendEvent(reply,address);
}
