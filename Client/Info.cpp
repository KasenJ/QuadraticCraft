#include "Info.h"

Info::Info(QWidget *parent) :
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

void Info::pop()
{
	if(!isPop&&animation->state()==QAbstractAnimation::Stopped){
		animation->setStartValue(pos());
		animation->setEndValue(pos()+QPoint(200,0));
		animation->start();
		isPop=true;
	}
}

void Info::push()
{
	if(isPop&&animation->state()==QAbstractAnimation::Stopped){
		animation->setStartValue(pos());
		animation->setEndValue(pos()-QPoint(200,0));
		animation->start();
		isPop=false;
	}
}
