#ifndef PACK_H
#define PACK_H

#include <QtCore>
#include <QtWidgets>
#include "Types.h"
#include "Square.h"
#include "Produce.h"

class Pack:public QWidget
{
	Q_OBJECT
public:
	explicit Pack(QWidget *parent=0);
	int getIndex() const {return index;}
	bool isPopped() const {return isPop;}
	const Package &getPackage() const {return package;}
	
private:
	int index;
	bool isPop;
	bool isDrag;
	Package package;
	Produce *produce;
	QPropertyAnimation *animation;

	void paintEvent(QPaintEvent *e);
	void mouseMoveEvent(QMouseEvent *e);
	void mouseReleaseEvent(QMouseEvent *e);

	int getIndex(const QPoint &p) const;
	QRect mapRect(int i,int j) const;
	QPoint mapPosition(int i,int j) const;

public slots:
	void pop();
	void push();
	void setPackage(const Package &change);
	
};

#endif // PACK_H
