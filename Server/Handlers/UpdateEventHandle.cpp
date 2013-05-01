#include "Handler.h"

void Handler::UpdateEventHandle(const UpdateEvent &event,const QHostAddress &address)
{
	qDebug()<<"Get UpdateEvent";
	QSqlQuery query;
	QVector<BitType> bitmap;
	for(const QRect &rect:event.getRects()){
		int x=rect.x(),y=rect.y(),w=rect.width(),h=rect.height();
		QVector<BitType> bits(w*h,Bit::Black);
		for(int i=0;i<w;i++){
			query.prepare("SELECT Type,Position FROM Cube WHERE Position>=? AND Position<?");
			query.addBindValue(Utils::toInt(QPoint(x+i,y)));
			query.addBindValue(Utils::toInt(QPoint(x+i,y+h)));
			query.exec();
			while(query.next()){
				QPoint point=Utils::toPoint(query.value("Position").toInt());
				bits[(point.y()-y)*w+point.x()-x]=query.value("Type").toInt();
			}
		}
		bitmap+=bits;
		qDebug()<<"Rect"<<rect<<"Updated";
	}
	UpdateEvent reply=event;
	reply.setBitmap(bitmap);
	sendEvent(reply,address);
}
