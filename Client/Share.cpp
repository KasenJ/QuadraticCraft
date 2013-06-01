#include "Share.h"

Socket *Share::socket=NULL;
Square *Share::square=NULL;
QHostAddress Share::server;

Square::Square(QObject *parent):
	QObject(parent)
{
	bool exists=QFile::exists("Cache.db");
	data=QSqlDatabase::addDatabase("QSQLITE");
	data.setDatabaseName("Cache.db");
	data.open();
	QSqlQuery query;
	if(!exists){
		query.exec("PRAGMA auto_vacuum = 1;");
		query.exec("CREATE TABLE Cache (Type INTEGER, Pixmap BLOB, PRIMARY KEY(Type) );");
	}
	else{
		query.exec("SELECT Type,Pixmap FROM Cache");
		while(query.next()){
			const auto &t=query.value("Type").toInt();
			const auto &p=Utils::fromByteArray<QPixmap>(query.value("Pixmap").toByteArray());
			map.insert(t,p);
		}
	}
}

QPixmap Square::getPixmap(BitType t)
{
	if(load&&!map.contains(t)){
		blank.insert(t);
	}
	return map.value(t);
}

void Square::setPixmap(BitType t,const QPixmap &p)
{
	map.insert(t,p);
	QSqlQuery query;
	query.prepare("INSERT INTO Cache VALUES(?,?);");
	query.addBindValue(t);
	query.addBindValue(Utils::toByteArray(p));
	query.exec();
}

QList<QPixmap> Square::getPixmaps(SquareType s)
{
	BitType t;
	QList<QPixmap> l;
	do{
		t=s&0xFF;
		s=s>>8;
		l.prepend(getPixmap(t));
	}
	while(t>=128);
	return l;
}

bool Square::setLoad(bool enabled)
{
	load=enabled;
	if(load){
		return true;
	}
	else if(blank.isEmpty()){
		return false;
	}
	else{
		DataEvent e;
		QHash<QString,QByteArray> h;
		for(BitType t:blank){
			h.insert(QString("T:%1").arg(t),QByteArray());
		}
		e.setData(h);
		Share::sendEvent(e);
		blank.clear();
		return true;
	}
}

void Share::sendEvent(const Event &event)
{
	socket->sendEvent(event,server);
}
