#ifndef LOGIN_H
#define LOGIN_H

#include <QtGui>
#include <QtCore>
#include <QtWidgets>
#include <QtNetwork>
#include "Types.h"

class Login : public QDialog
{
	Q_OBJECT
public:
	explicit Login(QWidget *parent = 0);
	void setSocket(Socket *socket);
	const QHostAddress &getServer() const;

private:
	QHostAddress server;
	Socket *socket;
};

#endif // LOGIN_H
