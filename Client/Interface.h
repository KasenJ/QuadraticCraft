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
	Q_PROPERTY(QPoint midPoint READ getMid WRITE setMid)
public:
	explicit Interface(QWidget *parent=0);
	void setSocket(Socket *socket);
	void setServer(const QHostAddress &server);
	QPoint getMid(){return midPoint;}
	void setMid(const QPoint &mid){midPoint=mid;update();}

private:
	Buffer buffer;
	Socket *socket;
	QPoint midPoint;
	QPoint mousePoint;
	QHostAddress server;
	QHash<int,bool> keyState;
	QPropertyAnimation *animation;

	void paintEvent(QPaintEvent *e);
	void keyPressEvent(QKeyEvent *e);
	void keyReleaseEvent(QKeyEvent *e);
	void mouseMoveEvent(QMouseEvent *e);

public slots:
	void monitor();
};

#endif // EXEC_H
