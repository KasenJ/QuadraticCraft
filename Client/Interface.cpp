#include "Interface.h"

Interface::Interface(QWidget *parent):
	QWidget(parent)
{
	setFixedSize(800,600);
	setWindowTitle(tr("QuadraticCraft"));
	move(QApplication::desktop()->screenGeometry().center()-QPoint(400,300));
	QTimer *timer=new QTimer(this);
	timer->start(100);
	connect(timer,&QTimer::timeout,this,&Interface::monitor);
	connect(&buffer,SIGNAL(buffered()),this,SLOT(update()));
}

void Interface::setSocket(Socket *socket)
{
	this->socket=socket;
	connect(socket,&Socket::getUpdateEvent,&buffer,&Buffer::update);
}

void Interface::setServer(const QHostAddress &server)
{
	this->server=server;
}

void Interface::paintEvent(QPaintEvent *e)
{
	QPainter painter;
	painter.begin(this);
	painter.drawPixmap(0,0,buffer.getPixmap());
	painter.end();
	QWidget::paintEvent(e);
}

void Interface::keyPressEvent(QKeyEvent *e)
{
	state[e->key()]=true;
}

void Interface::keyReleaseEvent(QKeyEvent *e)
{
	state[e->key()]=false;
}

void Interface::monitor()
{
	auto move=[this](int x,int y){
		QRect rect=buffer.getRect();
		rect.moveTopLeft(rect.topLeft()+QPoint(x,y));
		buffer.setRect(rect);
	};
	if(state[Qt::Key_Left]||state[Qt::Key_A]){
		move(-1,0);
	}
	if(state[Qt::Key_Down]||state[Qt::Key_S]){
		move(0,+1);
	}
	if(state[Qt::Key_Right]||state[Qt::Key_D]){
		move(+1,0);
	}
	if(state[Qt::Key_Up]||state[Qt::Key_W]){
		move(0,-1);
	}
}
