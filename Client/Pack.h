#ifndef PACK_H
#define PACK_H

#include <QtCore>
#include <QtWidgets>
#include "Types.h"
#include "Square.h"

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
	Package package;
	QPropertyAnimation *animation;

	void paintEvent(QPaintEvent *e);
	void mousePressEvent(QMouseEvent *e);
	void mouseReleaseEvent(QMouseEvent *e);
	int getIndex(const QPoint &p) const;

public slots:
	void pop();
	void push();
	void setPackage(const Package &change);
	
};

#endif // PACK_H
