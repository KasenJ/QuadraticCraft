#include "Handler.h"

void Handler::DataEventHandle(const DataEvent &event,const QHostAddress &address)
{
	qDebug()<<"Get DataEvent";
	QSqlQuery query;
	QHash<QString,QByteArray> data=event.getData();
	qDebug()<<data;
	QList<QString> d=data.keys();
	bool flag=!d.isEmpty();
	for(QString item:d){
		if(item.startsWith("T:")){
			query.prepare("SELECT Texture FROM Bit WHERE Type=?");
			query.addBindValue(item.mid(2).toInt());
			query.exec();
			if(query.first()){
				data[item]=query.value("Texture").toByteArray();
			}
			else{
				flag=false;
				break;
			}
		}
	}
	if(flag){
		DataEvent reply;
		reply.setData(data);
		sendEvent(reply,address);
	}
}
