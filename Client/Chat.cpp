#include "Chat.h"

Chat::Chat(QWidget *parent):
	QWidget(parent)
{
	ioo=0;
	self=false;
	timer=new QTimer(this);
	delay=new QTimer(this);
	delay->setSingleShot(true);
	connect(timer,&QTimer::timeout,[this](){
		if(ioo==0){
			timer->stop();
		}
		else if(ioo==1){
			if(effect->opacity()>=0.9){
				effect->setOpacity(1.0);
				timer->stop();
				ioo=2;
			}
			else{
				effect->setOpacity(effect->opacity()+0.1);
			}
		}
		else if(ioo==3){
			if(effect->opacity()<=0.1){
				effect->setOpacity(0.0);
				timer->stop();
				ioo=0;
				hide();
			}
			else{
				effect->setOpacity(effect->opacity()-0.1);
			}
		}
	});
	connect(delay,&QTimer::timeout,[this](){
		if(!rect().contains(mapFromGlobal(QCursor::pos()))){
			self=false;
			fadeOut();
		}
	});
	effect=new QGraphicsOpacityEffect(this);
	effect->setOpacity(0.0);
	setGraphicsEffect(effect);
	line=new QLineEdit(this);
	connect(line,&QLineEdit::returnPressed,[this](){
		DataEvent e;
		QHash<QString,QByteArray> h;
		h.insert("C:",line->text().toUtf8());
		e.setData(h);
		Share::sendEvent(e);
		line->clear();
	});
	QFont f=font();
	f.setPointSize(10);
	setFont(f);
}

Chat::~Chat()
{
}

void Chat::paintEvent(QPaintEvent *e)
{
	QPainter painter;
	painter.begin(this);
	int h=height()-40;
	auto iter=list.begin();
	painter.fillRect(rect(),QColor(0,0,0,50));
	painter.setPen(Qt::gray);
	for(;h>=20&&iter!=list.end();++iter){
		h-=iter->size().height();
		painter.drawStaticText(10,h,*iter);
	}
	painter.end();
	list.erase(iter,list.end());
	QWidget::paintEvent(e);
}

void Chat::resizeEvent(QResizeEvent *)
{
	line->setGeometry(10,height()-30,width()-20,20);
}

void Chat::append(QString content)
{
	fadeIn();
	self=true;
	QTextOption o;
	o.setWrapMode(QTextOption::WordWrap);
	list.prepend(QStaticText(content));
	list.first().prepare(QTransform(),font());
	list.first().setTextOption(o);
	update();
	delay->start(5000);
}

void Chat::fadeIn()
{
	if(ioo==0){
		ioo=1;
		timer->start(50);
		show();
	}
	self=false;
}

void Chat::fadeOut()
{
	if(ioo==2&&!self){
		ioo=3;
		timer->start(50);
	}
}
