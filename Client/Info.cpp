#include "Info.h"

extern Square *square;

Info::Info(QWidget *parent) :
	QWidget(parent)
{
	isPop=false;
	setAutoFillBackground(true);
	animation=new QPropertyAnimation(this,"pos",this);
	animation->setDuration(200);
	animation->setEasingCurve(QEasingCurve::OutCubic);

	playerL=new QLabel(tr("Player"),this);
	playerL->setGeometry(QRect(10,25, 120,25));
	playerE=new QLineEdit(this);
	playerE->setReadOnly(true);
	playerE->setGeometry(QRect(10,60, 120,25));

	occuptL=new QLabel(tr("Occupation"),this);
	occuptL->setGeometry(QRect(10,105, 120,25));
	occuptE=new QLineEdit(this);
	occuptE->setReadOnly(true);
	occuptE->setGeometry(QRect(10,140, 120,25));

	pstionL=new QLabel(tr("Position"),this);
	pstionL->setGeometry(QRect(10,185, 120,25));
	pstionE=new QLineEdit(this);
	pstionE->setReadOnly(true);
	pstionE->setGeometry(QRect(10,220, 120,25));

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

void Info::setPlayer(QString player)
{
	playerE->setText(player);
}

void Info::setOccupation(QString occupation)
{
	occuptE->setText(occupation);
}

void Info::setPosition(QPoint position)
{
	current=position;
	QString text("(%1, %2)");
	pstionE->setText(text.arg(position.x()).arg(position.y()));
}
