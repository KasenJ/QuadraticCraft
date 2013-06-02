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
		query.exec("CREATE TABLE Cache (Type INTEGER, Pixmap BLOB, TEXT Name, TEXT Desc, PRIMARY KEY(Type) );");
	}
	else{
		query.exec("SELECT * FROM Cache");
		while(query.next()){
			const auto &t=query.value("Type").toInt();
			const auto &p=Utils::fromByteArray<QPixmap>(query.value("Pixmap").toByteArray());
			const auto &n=query.value("Name").toString();
			const auto &d=query.value("Desc").toString();
			pm.insert(t,p);
			nm.insert(t,n);
			dm.insert(t,d);
		}
	}
}

QPixmap Square::getPixmap(BitType t)
{
	if(load&&!pm.contains(t)){
		blank.insert(t);
	}
	return pm.value(t);
}

QString Square::getName(BitType t)
{
	return nm.value(t);
}

QString Square::getDesc(BitType t)
{
	return dm.value(t);
}

void Square::insertBit(BitType t,const QByteArray &a)
{
	QString n,d;
	QByteArray p;
	QDataStream s(a);
	s>>n>>d>>p;
	QSqlQuery query;
	query.prepare("INSERT INTO Cache VALUES(?,?,?,?);");
	query.addBindValue(t);
	query.addBindValue(p);
	query.addBindValue(n);
	query.addBindValue(d);
	query.exec();
	pm.insert(t,Utils::fromByteArray<QPixmap>(p));
	nm.insert(t,n);
	dm.insert(t,d);
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
