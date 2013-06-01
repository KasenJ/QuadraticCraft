#include "Handler.h"

void Handler::DataEventHandle(const DataEvent &event,const QHostAddress &address)
{
	qDebug()<<"Get DataEvent";
	QSqlQuery query;
	QHash<QString,QByteArray> data=event.getData();
	int flag=!data.isEmpty();
	for(QString item:data.keys()){
		if(item.startsWith("T:")){
			query.prepare("SELECT Texture FROM Bit WHERE Type=?");
			query.addBindValue(item.mid(2).toInt());
			query.exec();
			if(query.first()){
				data[item]=query.value("Texture").toByteArray();
			}
			else{
				flag=0;
				break;
			}
		}
		if(item.startsWith("C:")){
			flag=2;
			data[item]=QString(data[item]).prepend("[%1] ").arg(userMap[address]).toUtf8();
		}
	}
	DataEvent reply;
	reply.setData(data);
	if(flag==1){
		sendEvent(reply,address);
	}
	if(flag==2){
		broadEvent(reply);
	}
}
