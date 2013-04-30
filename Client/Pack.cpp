#include "Pack.h"

extern Square *square;

Pack::Pack(QWidget *parent):
	QWidget(parent)
{
	index=-1;
	isPop=false;
	setAutoFillBackground(true);
	QPalette options;
	options.setColor(QPalette::Background,Qt::white);
	setPalette(options);
	animation=new QPropertyAnimation(this,"pos",this);
	animation->setDuration(200);
	animation->setEasingCurve(QEasingCurve::OutCubic);
}

void Pack::paintEvent(QPaintEvent *e)
{
	QPainter painter;
	painter.begin(this);
	painter.setPen(Qt::gray);
	int i,j,c=0;
	for(i=0;i<4;++i){
		for(j=0;j<3;++j){
			painter.drawRect(12.5+62.5*j,15+65*i,50,50);
			if(c<package.size()){
				painter.drawPixmap(12.5+62.5*j,15+65*i,square->at(package[c].first));
				painter.drawText(16+62.5*j,62+65*i,QString("x%1").arg(package[c].second));
			}
			++c;
		}
	}
	if(index>=0){
		i=index/3;
		j=index%3;
		QPen pen;
		pen.setWidthF(2.5);
		pen.setColor(Qt::darkGray);
		pen.setJoinStyle(Qt::MiterJoin);
		painter.setPen(pen);
		painter.drawRect(12.5+62.5*j,15+65*i,50,50);
	}
	painter.end();
	QWidget::paintEvent(e);
}

void Pack::mouseReleaseEvent(QMouseEvent *e)
{
	bool flag=true;
	auto cursor=e->pos();
	for(int i=0;i<4;++i){
		for(int j=0;j<3;++j){
			if(QRect(12.5+62.5*j,15+65*i,50,50).contains(cursor)){
				index=i*3+j;
				flag=false;
				break;
			}
		}
	}
	if(flag){
		index=-1;
	}
	update();
	QWidget::mouseReleaseEvent(e);
}

void Pack::pop()
{
	if(!isPop&&animation->state()==QAbstractAnimation::Stopped){
		animation->setStartValue(pos());
		animation->setEndValue(pos()-QPoint(200,0));
		animation->start();
		isPop=true;
	}
}

void Pack::push()
{
	if(isPop&&animation->state()==QAbstractAnimation::Stopped){
		animation->setStartValue(pos());
		animation->setEndValue(pos()+QPoint(200,0));
		animation->start();
		isPop=false;
	}
}

void Pack::setPackage(const Package &change)
{
	for(auto item:change){
		bool flag=true;
		for(auto iter:package){
			if(iter.first==item.first){
				flag=false;
				iter.second+=item.second;
				break;
			}
		}
		if(flag){
			package.append(item);
		}
	}
}
