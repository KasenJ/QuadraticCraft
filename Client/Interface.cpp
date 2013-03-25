#include "Interface.h"

Interface::Interface(QWidget *parent):
	QWidget(parent)
{
	setMouseTracking(true);
	setWindowTitle(tr("QuadraticCraft"));
	setFixedSize(800,600);
	move(QApplication::desktop()->screenGeometry().center()-QPoint(400,300));
	midPoint=rect().center();
	mousePoint=midPoint;
	animation=new QPropertyAnimation(this,"midPoint",this);
	animation->setDuration(200);
	animation->setEasingCurve(QEasingCurve::Linear);
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
	QPixmap pixmap=buffer.getPixmap();
	painter.drawPixmap(midPoint-pixmap.rect().center(),pixmap);
	painter.end();
	QWidget::paintEvent(e);
}

void Interface::keyPressEvent(QKeyEvent *e)
{
	keyState[e->key()]=true;
}

void Interface::keyReleaseEvent(QKeyEvent *e)
{
	keyState[e->key()]=false;
}

void Interface::mouseMoveEvent(QMouseEvent *e)
{
	mousePoint=e->pos();
}

void Interface::monitor()
{
	auto move=[this](int x,int y){
		QRect current=buffer.getRect(),updated=current;
		updated.moveTopLeft(current.topLeft()+QPoint(x,y));
		buffer.setRect(updated);
		if(x*y!=0){
			;
		}
		else if(x==0){
			if(y>0){
				updated.setTop(current.bottom());
			}
			else{
				updated.setBottom(current.top());
			}
		}
		else if(y==0){
			if(x>0){
				updated.setLeft(current.right());
			}
			else{
				updated.setRight(current.left());
			}
		}
		UpdateEvent updateEvent;
		updateEvent.setRect(updated);
		socket->sendEvent(updateEvent,server);
	};
	if(keyState[Qt::Key_Left]||keyState[Qt::Key_A]){
		move(-1,0);
	}
	if(keyState[Qt::Key_Down]||keyState[Qt::Key_S]){
		move(0,+1);
	}
	if(keyState[Qt::Key_Right]||keyState[Qt::Key_D]){
		move(+1,0);
	}
	if(keyState[Qt::Key_Up]||keyState[Qt::Key_W]){
		move(0,-1);
	}

	if(animation->state()==QAbstractAnimation::Stopped){
		int x=mousePoint.x();
		if(x<50){
			animation->setStartValue(midPoint);
			animation->setEndValue(rect().center()+QPoint(200,0));
			animation->start();
		}
		if(x>750){
			animation->setStartValue(midPoint);
			animation->setEndValue(rect().center()-QPoint(200,0));
			animation->start();
		}
		if(x>200&&x<600&&midPoint!=rect().center()){
			animation->setStartValue(midPoint);
			animation->setEndValue(rect().center());
			animation->start();
		}
	}
}
