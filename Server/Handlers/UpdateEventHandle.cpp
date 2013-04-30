#include "Handler.h"

void Handler::UpdateEventHandle(const UpdateEvent &event,const QHostAddress &address)
{
	qDebug()<<"Get UpdateEvent";
	const QRect rect=event.getRect();
	QVector<BitType> bitmap;
	QSqlQuery query;
	bool flag;
	int x=rect.x(),y=rect.y(),w=rect.width(),h=rect.height();
	QVector<BitType> temp[w];
	for(int j=x;j<x+w;j++){
		query.prepare("SELECT Type FROM Cube WHERE Position>=? AND Position<=?");
		query.addBindValue(j<<16+y);
		query.addBindValue(j<<16+y+h);
		flag=query.exec();
		if(flag) qDebug()<<"Query Cube In The UpdateEventHandle Successed";
		else qDebug()<<"Query Cube In The UpdateEventHandle Failed";
		if(query.first()){
			qDebug()<<"Start To Update Bitmap From Point "<<j<<","<<y<<" In The UpdateEventHandle";
			while(query.next()){
				int type=query.value("Type").toInt();
				temp[j-x].append(type);
			}
		}
		else qDebug()<<"Update Bitmap From Point "<<j<<","<<y<<"In The UpdateEventHandle Failed";
	}
	for(int i=0;i<h;i++){
		for(int j=0;j<w;j++){
			bitmap.append(temp[j].at(i));
		}
	}
	UpdateEvent reply;
	reply.setRect(rect);
	reply.setBitmap(bitmap);
	sendEvent(reply,address);
}
