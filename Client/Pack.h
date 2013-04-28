#ifndef PACK_H
#define PACK_H

#include <QtCore>
#include <QtWidgets>

class Pack:public QWidget
{
	Q_OBJECT
public:
	explicit Pack(QWidget *parent=0);
	bool isPopped(){return isPop;}
	
private:
	bool isPop;
	QPropertyAnimation *animation;

public slots:
	void pop();
	void push();
	
};

#endif // PACK_H
