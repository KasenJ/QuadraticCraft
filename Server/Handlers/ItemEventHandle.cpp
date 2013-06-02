#include "Handler.h"

void Handler::ItemEventHandle(const ItemEvent &event,const QHostAddress &address)
{
	qDebug()<<"Get ItemEvent";
	switch(event.getOperation())
	{
	case ItemEvent::Get:
	{
		QSqlQuery query;
		query.prepare("SELECT Cube.Type FROM Cube,Bit Where Position=? AND Take=1 AND Bit.Type=Cube.Type%256");
		query.addBindValue(Utils::toInt(event.getPoint()));
		query.exec();
		if(query.first()){
			SquareType type=query.value("Type").toULongLong();
			BitType bit=type&0xFF;
			query.prepare("SELECT * FROM Cell WHERE PName=? AND Item=?");
			query.addBindValue(userMap[address]);
			query.addBindValue(bit);
			query.exec();
			if(query.first()){
				int number=query.value("Number").toInt();
				query.prepare("UPDATE Cell SET Number=? WHERE PName=? AND Item=?");
				query.addBindValue(++number);
				query.addBindValue(userMap[address]);
				query.addBindValue(bit);
			}
			else{
				query.prepare("INSERT INTO Cell (PName,Item,Number)""VALUES(?,?,?)");
				query.addBindValue(userMap[address]);
				query.addBindValue(bit);
				query.addBindValue(1);
			}
			query.exec();
			query.prepare("SELECT Info FROM Player,Bit WHERE PName=? AND Occupation=Type");
			query.addBindValue(userMap[address]);
			query.exec();
			if(query.first()){
				QDataStream s(query.value("Info").toByteArray());
				QString n,d;
				QHash <BitType,BitType> h;
				s>>n>>d>>h;
				if(h.contains(bit)){
					query.prepare("UPDATE Player SET Occupation=? WHERE PName=?");
					query.addBindValue(h[bit]);
					query.addBindValue(userMap[address]);
					query.exec();
					ScriptEvent s;
					Dialog dia;
					dia.append(QPair<QString,quint32>(QString("转职为%1成功").arg(n),1000));
					dia.append(QPair<QString,quint32>(QString("职业描述:%1").arg(d),2000));
					s.setDialog(dia);
					sendEvent(s,address);

					UpdateEvent update;
					QList<Role> roles;
					query.prepare("SELECT Occupation,Position FROM Player;");
					query.exec();
					while(query.next()){
						auto b=query.value("Occupation").toInt();
						auto p=Utils::toPoint(query.value("Position").toInt());
						roles.append(Role(b,p));
					}
					update.setRoles(roles);
					broadEvent(update);
				}
			}
			PlayerEvent reply;
			Package change={Cell(bit,1)};
			reply.setPackege(change);
			sendEvent(reply,address);

			type=type>>8;
			query.prepare("UPDATE Cube SET Type=? Where Position=?");
			query.addBindValue(type);
			query.addBindValue(Utils::toInt(event.getPoint()));
			query.exec();

			UpdateEvent broad;
			broad.setRect(QRect(event.getPoint(),QSize(1,1)));
			broad.setBitmap(Bitmap(1,type));
			broadEvent(broad);
		}
		else{
			qDebug()<<"Can Not Take";
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
				SquareType type=query.value("Type").toULongLong();
				if(number>=2){
					query.prepare("UPDATE Cell SET Number=? WHERE PName=? AND Item=?");
					query.bindValue(0,--number);
					query.bindValue(1,userMap[address]);
					query.bindValue(2,_type);
				}
				else{
					query.prepare("DELETE FROM Cell WHERE PName=? AND Item=?");
					query.bindValue(0,userMap[address]);
					query.bindValue(1,_type);
				}
				query.exec();

				query.prepare("UPDATE Cube SET TYPE=? WHERE POSITION=?");
				query.bindValue(0,(type<<8)+_type);
				query.bindValue(1,Utils::toInt(event.getPoint()));
				query.exec();

				PlayerEvent reply;
				Package change={Cell(_type,-1)};
				reply.setPackege(change);
				sendEvent(reply,address);

				UpdateEvent broad;
				broad.setRect(QRect(event.getPoint(),QSize(1,1)));
				broad.setBitmap(Bitmap(1,_type));
				broadEvent(broad);
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
		query.addBindValue(userMap[address]);
		query.exec();
		Package all;
		while(query.next()){
			auto i=query.value("Item").value<BitType>();
			auto n=query.value("Number").value<qint32>();
			all.append(qMakePair(i,n));
		}
		bool flag=true;
		Package c=event.getPackage();
		for(const Cell &item:c){
			bool exists=false;
			for(const Cell &i:all){
				if(i.first==item.first){
					if(i.second>=item.second){
						exists=true;
					}
					break;
				}
			}
			if(!exists){
				flag=false;
				break;
			}
		}
		qSort(c.begin(),c.end(),[](const Cell &f,const Cell &s){return f.first<s.first;});
		if(flag){
			PlayerEvent reply;
			Package change;
			quint32 comp=0;
			qint8 min=128-1;
			for(const Cell &cell:c){
				comp=(comp<<8)+cell.first;
				min=min<cell.second?min:cell.second;
			}
			query.prepare("SELECT Product FROM Formula,Player WHERE PName=? AND Player.Occupation=Formula.Occupation And Composition=?");
			query.addBindValue(userMap[address]);
			query.addBindValue(comp);
			query.exec();
			if(query.first()){
				int p=query.value("Product").toInt()&0xFF;
				for(const Cell &item:c){
					if(item.second==min){
						query.prepare("DELETE FROM Cell WHERE PName=? And Item=? ");
						query.addBindValue(userMap[address]);
						query.addBindValue(item.first);
						query.exec();
					}
					else{
						query.prepare("UPDATE Cell SET Number=? WHERE PName=? And Item=? ");
						query.addBindValue(item.second-min);
						query.addBindValue(userMap[address]);
						query.addBindValue(item.first);
						query.exec();
					}
					change.append(Cell(item.first,-min));
				}
				int t=0;
				for(const Cell &item:all){
					if(item.first==p){
						t=item.second;
						break;
					}
				}
				if(t>0){
					query.prepare("UPDATE Cell SET Number=? WHERE PName=? And Item=? ");
					query.addBindValue(t+min);
					query.addBindValue(userMap[address]);
					query.addBindValue(p);
					query.exec();
				}
				else{
					query.prepare("INSERT INTO Cell VALUES(?,?,?)");
					query.addBindValue(userMap[address]);
					query.addBindValue(p);
					query.addBindValue(min);
					query.exec();
				}
				change.append(Cell(p,min));
			}
			else{
				qDebug()<<"No Such Formula";
			}
			reply.setPackege(change);
			sendEvent(reply,address);
		}
		else{
			qDebug()<<"No Such Items In Package";
		}
	}
	}
}
