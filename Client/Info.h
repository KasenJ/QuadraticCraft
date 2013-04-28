#ifndef INFO_H
#define INFO_H

#include <QtCore>
#include <QtWidgets>

class Info:public QWidget
{
	Q_OBJECT
public:
	explicit Info(QWidget *parent=0);
	bool isPopped(){return isPop;}

private:
	bool isPop;
	QPropertyAnimation *animation;

public slots:
	void pop();
	void push();
	
};

#endif // INFO_H
