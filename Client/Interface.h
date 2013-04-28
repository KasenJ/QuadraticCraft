#ifndef EXEC_H
#define EXEC_H

#include <QtGui>
#include <QtCore>
#include <QtWidgets>
#include <QtNetwork>
#include "Types.h"
#include "Info.h"
#include "Pack.h"
#include "Buffer.h"

class Interface:public QWidget
{
	Q_OBJECT
public:
	explicit Interface(QWidget *parent=0);
	void setSocket(Socket *socket);
	void setServer(const QHostAddress &server);

private:
	Info *info;
	Pack *pack;
	Buffer buffer;
	Socket *socket;
	QHostAddress server;
	QHash<int,bool> keyState;

	void paintEvent(QPaintEvent *e);
	void resizeEvent(QResizeEvent *e);
	void keyPressEvent(QKeyEvent *e);
	void keyReleaseEvent(QKeyEvent *e);

};

#endif // EXEC_H
