#ifndef EXEC_H
#define EXEC_H

#include <QtGui>
#include <QtCore>
#include <QtWidgets>
#include <QtNetwork>
#include "Info.h"
#include "Pack.h"
#include "Chat.h"
#include "Types.h"
#include "Share.h"
#include "Buffer.h"

class Interface:public QWidget
{
	Q_OBJECT
public:
	explicit Interface(QWidget *parent=0);
	~Interface();

private:
	int blocked;
	Info *info;
	Pack *pack;
	Chat *chat;
	Buffer *buffer;
	QLabel *script;
	QHash<int,bool> keyState;

	void paintEvent(QPaintEvent *e);
	void resizeEvent(QResizeEvent *e);
	void keyPressEvent(QKeyEvent *e);
	void keyReleaseEvent(QKeyEvent *e);
	void mouseReleaseEvent(QMouseEvent *e);

};

#endif // EXEC_H
