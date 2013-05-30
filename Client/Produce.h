#ifndef PRODUCE_H
#define PRODUCE_H

#include <QtCore>
#include <QtWidgets>
#include "Types.h"
#include "Square.h"

class Produce:public QFrame
{
	Q_OBJECT
public:
	explicit Produce(QWidget *parent=0);

private:
	Package items;
	QList<int> count;
	void dropEvent(QDropEvent *e);
	void paintEvent(QPaintEvent *e);
	void wheelEvent(QWheelEvent *e);
	void dragEnterEvent(QDragEnterEvent *e);

signals:
	void produce(Package);
	
};

#endif // PRODUCE_H
