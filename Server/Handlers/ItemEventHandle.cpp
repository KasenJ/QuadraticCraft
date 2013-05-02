#include "Handler.h"

void Handler::ItemEventHandle(const ItemEvent &event,const QHostAddress &address)
{
	qDebug()<<"Get ItemEvent";
	switch(event.getOperation())
	{
	case ItemEvent::Get:
	{
		QSqlQuery query;
		query.prepare("SELECT Type FROM Cube Where Position=?");
		query.addBindValue(Utils::toInt(event.getPoint()));
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
			Package change={(QPair<BitType,qint8>(type,1))};
			reply.setPackege(change);
			sendEvent(reply,address);

			query.prepare("UPDATE Cube SET Type=? Where Position=?");
			query.addBindValue(type>>=8);
			query.addBindValue(Utils::toInt(event.getPoint()));
			query.exec();

			UpdateEvent broad;
			QList<QRect> rects={QRect(event.getPoint(),QSize(1,1))};
			QVector<BitType> bitmap={static_cast<BitType>(type)};
			broad.setRects(rects);
			broad.setBitmap(bitmap);
			for(auto user:userMap.keys()){
				sendEvent(broad,user);
			}

			qDebug()<<"Get"<<event.getPoint();
		}
		else{
			qDebug()<<"No such item in Cube";
		}
		break;
	}
	case ItemEvent::Drop:
	{
		QSqlQuery query;
		query.prepare("SELECT Number FROM Cell WHERE PName=? AND Item=?");
		BitType _type=event.getPackage().first().first;
		query.addBindValue(userMap[address]);
		query.addBindValue(_type);
		query.exec();
		if(query.first()){
			int number=query.value("Number").toInt();
			query.prepare("SELECT Type FROM Cube WHERE POSITION=?");
			query.bindValue(0,Utils::toInt(event.getPoint()));
			query.exec();
			if(query.first()){
				BitType type=query.value("Type").toInt();
				if(number>=2){
					query.prepare("UPDATE Cell SET Number=? WHERE PName=? AND Item=?");
					query.bindValue(0,--number);
					query.bindValue(1,userMap[address]);
					query.bindValue(2,_type);
				}
				else{
					query.prepare("DELETE Cell WHERE PName=? AND Item=?");
					query.bindValue(0,userMap[address]);
					query.bindValue(1,_type);
				}
				query.exec();

				query.prepare("UPDATE Cube SET TYPE=? WHERE POSITION=?");
				query.bindValue(0,(type<<8)+_type);
				query.bindValue(1,Utils::toInt(event.getPoint()));
				query.exec();

				PlayerEvent reply;
				Package change={(QPair<BitType,qint8>(_type,-1))};
				reply.setPackege(change);
				sendEvent(reply,address);

				UpdateEvent broad;
				QList<QRect> rects={QRect(event.getPoint(),QSize(1,1))};
				QVector<BitType> bitmap={static_cast<BitType>(_type)};
				broad.setRects(rects);
				broad.setBitmap(bitmap);
				for(auto user:userMap.keys()){
					sendEvent(broad,user);
				}

				qDebug()<<"Drop"<<event.getPoint();
			}
			else{
				qDebug()<<"No Space To Drop";
			}
		}
		else{
			qDebug()<<"No Such Item In Package";
		}
		break;
	}
	case ItemEvent::Produce:
	{
		QSqlQuery query;
		query.prepare("SELECT Item,Number FROM Cell WHERE PName=?");
		query.exec();
		Package all;
		while(query.next()){
			auto i=query.value("Item").value<BitType>();
			auto n=query.value("Number").value<qint8>();
			all.append(qMakePair(i,n));
		}
		bool flag=true;
		Package change=event.getPackage();
		for(auto &item:change){
			if(all.indexOf(item)==-1){
				flag=false;
				break;
			}
			auto &n=item.second;
			n=n>0?-n:n;
		}
		if(flag){
			PlayerEvent reply;
			reply.setPackege(change);
			sendEvent(reply,address);
		}
		else{
			qDebug()<<"No Such Items In Package";
		}
	}
	}
}
