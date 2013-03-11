#ifndef EXEC_H
#define EXEC_H

#include <QtGui>
#include <QtCore>
#include <QtWidgets>
#include <QtNetwork>
#include "Types.h"
#include "Buffer.h"

class Interface:public QWidget
{
	Q_OBJECT
public:
	explicit Interface(QWidget *parent=0);
	void setSocket(Socket *socket);
	void setServer(const QHostAddress &server);

private:
	Buffer buffer;
	Socket *socket;
	QHostAddress server;
	QHash<int,bool> state;

	void paintEvent(QPaintEvent *e);
	void keyPressEvent(QKeyEvent *e);
	void keyReleaseEvent(QKeyEvent *e);

public slots:
	void monitor();
};

#endif // EXEC_H
