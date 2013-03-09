#include "Interface.h"

Interface::Interface(QWidget *parent):
	QWidget(parent)
{
	setFixedSize(800,600);
	setWindowTitle(tr("QuadraticCraft"));
	move(QApplication::desktop()->screenGeometry().center()-QPoint(400,300));
	buffer=QPixmap(800,600);
}

void Interface::setSocket(Socket *socket)
{
	this->socket=socket;
	connect(socket,&Socket::getUpdateEvent,this,&Interface::render);
}

void Interface::setServer(const QHostAddress &server)
{
	this->server=server;
}

void Interface::paintEvent(QPaintEvent *e)
{
	QPainter painter;
	painter.begin(this);
	painter.drawPixmap(0,0,800,600,buffer);
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

void Interface::render(const UpdateEvent &event)
{
	if(event.isValid()){
		auto &rect=event.getRect();
		auto &bitmap=event.getBitmap();
		QPainter painter;
		painter.begin(&buffer);
		for(int i=0;i<rect.width();i++){
			for(int j=0;j<rect.height();j++){
				painter.drawPixmap(i*50,j*50,50,50,square[bitmap[i*rect.height()+j]]);
			}
		}
		painter.end();
		update();
	}
}

void Interface::monitor()
{
	if(state[Qt::Key_Left]||state[Qt::Key_A]){
		;
	}
}
