#ifndef HANDLER_H
#define HANDLER_H

#include <QtSql>
#include <QtCore>
#include <QtNetwork>
#include "Types.h"

class Handler:public QObject
{
	Q_OBJECT
public:
	explicit Handler(QObject *parent=0);
	~Handler();
	void setSocket(Socket *socket);

private:
	Socket *socket;
	QSqlDatabase data;
	QHash<QHostAddress,QString> userMap;
	inline void sendEvent(const Event &event,const QHostAddress &address){socket->sendEvent(event,address);}

public slots:
	void ItemEventHandle(const ItemEvent &event,const QHostAddress &address);
	void PlayerEventHandle(const PlayerEvent &event,const QHostAddress &address);
	void UpdateEventHandle(const UpdateEvent &event,const QHostAddress &address);
	void UserEventHandle(const UserEvent &event,const QHostAddress &address);
};

#endif // HANDLER_H
