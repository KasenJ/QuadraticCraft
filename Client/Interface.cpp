#include "Interface.h"

Interface::Interface(QWidget *parent):
	QWidget(parent)
{
	blocked=0;
	info=new Info(this);
	pack=new Pack(this);
	chat=new Chat(this);
	buffer=new Buffer(this);
	script=new QLabel(this);
	Share::square=new Square(this);
	script->setGeometry(210,600,380,100);
	script->setAlignment(Qt::AlignCenter);
	script->setAutoFillBackground(true);
	setMouseTracking(true);
	setWindowTitle(tr("QuadraticCraft"));
	setFixedSize(800,600);
	move(QApplication::desktop()->screenGeometry().center()-QPoint(400,300));
	auto timer=new QTimer(this);
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
			Share::sendEvent(playerEvent);
		}

		auto cursor=mapFromGlobal(QCursor::pos());
		int x=cursor.x(),y=cursor.y();

		if(x<-50||x>width()+50||y<-50||y>height()+50){
			info->push();
			pack->push();
			chat->fadeOut();
		}
		else{
			if(x>250){
				info->push();
			}
			if(x<width()-250){
				pack->push();
			}
			if(x>500||y<350){
				chat->fadeOut();
			}
			if(!blocked&&x<50){
				info->pop();
			}
			if(!blocked&&x>width()-50){
				pack->pop();
			}
			if(x<450&&y>height()-50){
				chat->fadeIn();
			}
		}
	});
	connect(Share::socket,&Socket::getPlayerEvent,[this](const PlayerEvent &e){
		if(!e.getPosition().isNull()){
			info->setPosition(e.getPosition());
			auto curPos=info->getPosition();
			auto curRct=buffer->getRect();
			if(curRct.isNull()){
				curRct=QRect(0,0,16,12);
				curRct.moveCenter(curPos);
				buffer->setRect(curRct);
			}
			else{
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
				}
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
	});
	connect(Share::socket,&Socket::getScriptEvent,[this](const ScriptEvent &e){
		if(!e.getDialog().isEmpty()){
			++blocked;
			QTimer *delay=new QTimer(this);
			delay->setSingleShot(true);
			Dialog *dialog=new Dialog(e.getDialog());
			QPropertyAnimation *anime=new QPropertyAnimation(script,"pos",this);
			anime->setEasingCurve(QEasingCurve::OutCubic);
			anime->setDuration(500);
			anime->setStartValue(script->pos());
			anime->setEndValue(QPoint(script->pos().x(),height()-100));
			anime->start();
			connect(anime,&QPropertyAnimation::finished,[=]{
				if(dialog->isEmpty()){
					delete dialog;
					--blocked;
				}
				else{
					delay->start(0);
				}
			});
			connect(delay,&QTimer::timeout,[=](){
				if(dialog->isEmpty()){
					delay->deleteLater();
					anime->setDuration(500);
					anime->setStartValue(script->pos());
					anime->setEndValue(QPoint(script->pos().x(),height()));
					anime->start();
				}
				else{
					const auto &cur=dialog->takeFirst();
					script->setText(cur.first);
					delay->start(cur.second);
				}
			});
		}
		if(!e.getMotion().isEmpty()){
			++blocked;
			QTimer *delay=new QTimer(this);
			delay->start(100);
			Track *motion=new Track(e.getMotion());
			connect(delay,&QTimer::timeout,[=](){
				if(motion->isEmpty()){
					delay->deleteLater();
					delete motion;
					--blocked;
				}
				else{
					auto &cur=motion->first();
					if(cur.second>0){
						cur.second-=100;
						PlayerEvent playerEvent;
						QPoint c=info->getPosition();
						QPoint m=cur.first.p2()-c;
						if(!m.isNull()){
							if(qAbs(m.x())>qAbs(m.y())){
								m=m.x()>0?QPoint(1,0):QPoint(-1,0);
							}
							else{
								m=m.y()>0?QPoint(0,1):QPoint(0,-1);
							}
							playerEvent.setPosition(c+m);
							Share::sendEvent(playerEvent);
						}
					}
					else{
						motion->removeFirst();
					}
				}
			});
		}
	});
	connect(Share::socket,&Socket::getUpdateEvent,[this](const UpdateEvent &e){
		if(!e.getRoles().isEmpty()){
			buffer->setRoles(e.getRoles());
		}
		if(!e.getBitmap().isEmpty()&&!e.getRects().isEmpty()){
			buffer->setBitmap(e.getBitmap(),e.getRects());
		}
		Share::square->setLoad(true);
		update();
		Utils::delayExec(200,[this](){
			if(Share::square->setLoad(false)){
				++blocked;
			}
		});
	});
	connect(Share::socket,&Socket::getDataEvent,[this](const DataEvent &e){
		bool unlocked=false;
		QHash<QString,QByteArray> d=e.getData();
		for(QString item:d.keys()){
			if(item.startsWith("T:")){
				if(!unlocked){
					unlocked=true;
					--blocked;
				}
				Share::square->setPixmap(item.mid(2).toInt(),Utils::fromByteArray<QPixmap>(d[item]));
			}
			if(item.startsWith("C:")){
				chat->append(d[item]);
			}
		}
		update();
	});
}

Interface::~Interface()
{
	UserEvent event;
	event.setUsername(info->getPlayerName());
	event.setState(UserEvent::Logout);
	Share::sendEvent(event);
}

void Interface::paintEvent(QPaintEvent *e)
{
	QPainter painter;
	painter.begin(this);
	buffer->draw(&painter);
	painter.end();
	QWidget::paintEvent(e);
}

void Interface::resizeEvent(QResizeEvent *e)
{
	int w=e->size().width(),h=e->size().height();
	info->setGeometry(info->isPopped()?0:0-200,0,200,h);
	pack->setGeometry(pack->isPopped()?w-200:w,0,200,h);
	chat->setGeometry(0,height()-300,450,300);
	QWidget::resizeEvent(e);
}

void Interface::keyPressEvent(QKeyEvent *e)
{
	keyState[e->key()]=blocked?false:true;
}

void Interface::keyReleaseEvent(QKeyEvent *e)
{
	keyState[e->key()]=false;
}

void Interface::mouseReleaseEvent(QMouseEvent *e)
{
	if(!info->isPopped()&&!pack->isPopped()&&!blocked){
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
		Share::sendEvent(itemEvent);
	}
}
