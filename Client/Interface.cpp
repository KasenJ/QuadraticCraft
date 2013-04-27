#include "Interface.h"

Interface::Interface(QWidget *parent):
	QWidget(parent)
{
	setMouseTracking(true);
	setWindowTitle(tr("QuadraticCraft"));
	setFixedSize(800,600);
	move(QApplication::desktop()->screenGeometry().center()-QPoint(400,300));
	auto timer=new QTimer(this);
	timer->start(100);
	connect(timer,&QTimer::timeout,this,&Interface::monitor);
	connect(&buffer,SIGNAL(buffered()),this,SLOT(update()));
	info=new Info(this);
	pack=new Pack(this);
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
	painter.drawPixmap(0,0,pixmap);
	painter.end();
	QWidget::paintEvent(e);
}

void Interface::resizeEvent(QResizeEvent *e)
{
	int w=e->size().width(),h=e->size().height();
	info->setGeometry(QRect(info->isPopped()?0:0-200,0,200,h));
	pack->setGeometry(QRect(pack->isPopped()?w-200:w,0,200,h));
	QWidget::resizeEvent(e);
}

void Interface::keyPressEvent(QKeyEvent *e)
{
	keyState[e->key()]=true;
}

void Interface::keyReleaseEvent(QKeyEvent *e)
{
	keyState[e->key()]=false;
}

void Interface::monitor()
{
	auto move=[this](int x,int y){
		QRect current=buffer.getRect(),updated=current;
		updated.moveTopLeft(current.topLeft()+QPoint(x,y));
		buffer.setRect(updated);
		if(x==0){
			if(y>0){
				updated.setTop(current.bottom());
			}
			else{
				updated.setBottom(current.top());
			}
		}
		if(y==0){
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

	auto cursor=mapFromGlobal(QCursor::pos());
	int x=cursor.x(),y=cursor.y();

	if(x<-50||x>width()+50||y<-50||y>width()+50){
		info->push();
		pack->push();
	}
	else{
		if(x>250){
			info->push();
		}
		if(x<width()-250){
			pack->push();
		}
		if(x<50){
			info->pop();
		}
		if(x>width()-50){
			pack->pop();
		}
	}

}
