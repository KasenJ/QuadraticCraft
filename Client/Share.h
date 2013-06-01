#ifndef SHARE_H
#define SHARE_H

#include <QtGui>
#include <QtSql>
#include <QtCore>
#include "Types.h"

class Square:public QObject
{
	Q_OBJECT
public:
	explicit Square(QObject *parent=0);
	QPixmap getPixmap(BitType t);
	void setPixmap(BitType t,const QPixmap &p);
	QList<QPixmap> getPixmaps(SquareType s);
	bool setLoad(bool enabled);

private:
	bool load=false;
	QSqlDatabase data;
	QSet<BitType> blank;
	QHash<quint8,QPixmap> map;

};

class Share
{
public:
	static Square *square;
	static Socket *socket;
	static QHostAddress server;
	static void sendEvent(const Event &event);
};


#endif // SHARE_H
