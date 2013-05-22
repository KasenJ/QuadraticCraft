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
	QLineEdit *address;
	QLineEdit *username;
	QLineEdit *password;
	QDialogButtonBox *button;
	Socket *socket;
	QHostAddress server;

	void showEvent(QShowEvent *e);
};

#endif // LOGIN_H
