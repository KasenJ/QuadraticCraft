#include "Pack.h"

Pack::Pack(QWidget *parent):
	QWidget(parent)
{
	isPop=false;
	setAutoFillBackground(true);
	QPalette options;
	options.setColor(QPalette::Background,Qt::white);
	setPalette(options);
	animation=new QPropertyAnimation(this,"pos",this);
	animation->setDuration(200);
	animation->setEasingCurve(QEasingCurve::OutCubic);
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
