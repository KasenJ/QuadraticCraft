#ifndef LOGIN_H
#define LOGIN_H

#include <QtGui>
#include <QtCore>
#include <QtWidgets>
#include <QtNetwork>
#include "Types.h"
#include "Share.h"

class Login : public QDialog
{
	Q_OBJECT
public:
	explicit Login(QWidget *parent = 0);

private:
	QLineEdit *address;
	QLineEdit *username;
	QLineEdit *password;
	QDialogButtonBox *button;

	void showEvent(QShowEvent *e);
};

#endif // LOGIN_H
