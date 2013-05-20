#include "Interface.h"

Square *square=NULL;

Interface::Interface(QWidget *parent):
	QWidget(parent)
{
	info=new Info(this);
	pack=new Pack(this);
	buffer=new Buffer(this);
	setMouseTracking(true);
	setWindowTitle(tr("QuadraticCraft"));
	setFixedSize(800,600);
	move(QApplication::desktop()->screenGeometry().center()-QPoint(400,300));
	square=new Square;auto timer=new QTimer(this);
	timer->start(100);
	connect(timer,&QTimer::timeout,[this](){
		QPoint move(0,0);
		if(keyState[Qt::Key_Left]||keyState[Qt::Key_A]){
			move+=QPoint(-1,0);
		}
		if(keyState[Qt::Key_Down]||keyState[Qt::Key_S]){
			move+=QPoint(0,+1);
		}
		if(keyState[Qt::Key_Right]||keyState[Qt::Key_D]){
			move+=QPoint(+1,0);
		}
		if(keyState[Qt::Key_Up]||keyState[Qt::Key_W]){
			move+=QPoint(0,-1);
		}
		if(!move.isNull()){
			PlayerEvent playerEvent;
			playerEvent.setPosition(info->getPosition()+move);
			socket->sendEvent(playerEvent,server);
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
	});
}

void Interface::setSocket(Socket *socket)
{
	this->socket=socket;
	connect(socket,&Socket::getPlayerEvent,[this](const PlayerEvent &e){
		if(!e.getPosition().isNull()){
			info->setPosition(e.getPosition());
			auto curPos=info->getPosition();
			auto curRct=buffer->getRect();
			QRect core(QPoint(0,0),curRct.size()/=2);
			core.moveCenter(curRct.center());
			if(!core.contains(curPos)){
				QRect updated=curRct;
				if(curPos.x()<core.left()){
					core.moveLeft(curPos.x());
				}
				if(curPos.x()>core.right()){
					core.moveRight(curPos.x());
				}
				if(curPos.y()<core.top()){
					core.moveTop(curPos.y());
				}
				if(curPos.y()>core.bottom()){
					core.moveBottom(curPos.y());
				}
				updated.moveCenter(core.center());
				buffer->setRect(updated);
				UpdateEvent updateEvent;
				QList<QRect> rects={updated};
				updateEvent.setRects(rects);
				this->socket->sendEvent(updateEvent,server);
			}
		}
		if(!e.getPackage().isEmpty()){
			pack->setPackage(e.getPackage());
		}
		if(!e.getName().isEmpty()){
			info->setPlayer(e.getName());
		}
		if(!e.getOccupation().isEmpty()){
			info->setOccupation(e.getOccupation());
		}
		update();
	});
	connect(socket,&Socket::getScriptEvent,[this](const ScriptEvent &e){
		;
	});
	connect(socket,&Socket::getUpdateEvent,[this](const UpdateEvent &e){
		buffer->setBitmap(e.getBitmap(),e.getRects());
		update();
	});
}

void Interface::setServer(const QHostAddress &server)
{
	this->server=server;
}

void Interface::paintEvent(QPaintEvent *e)
{
	QPainter painter;
	painter.begin(this);
	buffer->draw(&painter);
	info->draw(&painter,buffer->getRect());
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

void Interface::mouseReleaseEvent(QMouseEvent *e)
{
	if(!info->isPopped()&&!pack->isPopped()){
		ItemEvent itemEvent;
		QPoint click=e->pos();
		click=buffer->getRect().topLeft()+QPoint(click.x()/50,click.y()/50);
		itemEvent.setPoint(click);
		if(e->button()==Qt::RightButton&&pack->getIndex()!=-1){
			itemEvent.setOperation(ItemEvent::Drop);
			auto item=pack->getPackage()[pack->getIndex()];
			item.second=1;
			Package change={item};
			itemEvent.setPackege(change);
		}
		if(e->button()==Qt::LeftButton){
			itemEvent.setOperation(ItemEvent::Get);
		}
		socket->sendEvent(itemEvent,server);
	}
}
