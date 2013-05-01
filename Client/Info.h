#ifndef INFO_H
#define INFO_H

#include <QtGui>
#include <QtCore>
#include <QtWidgets>
#include "Square.h"

class Info:public QWidget
{
	Q_OBJECT
public:
	explicit Info(QWidget *parent=0);
	void draw(QPainter *painter,QRect rect);
	bool isPopped(){return isPop;}
	inline const QPoint &getPosition() const {return current;}

private:
	bool isPop;
	QPoint current;
	QLabel *playerL;
	QLabel *occuptL;
	QLabel *pstionL;
	QLineEdit *playerE;
	QLineEdit *occuptE;
	QLineEdit *pstionE;
	QPropertyAnimation *animation;

public slots:
	void pop();
	void push();
	void setPlayer(QString player);
	void setPosition(QPoint position);
	void setOccupation(QString occupation);
	
};

#endif // INFO_H
