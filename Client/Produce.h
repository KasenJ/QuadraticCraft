#ifndef PRODUCE_H
#define PRODUCE_H

#include <QtCore>
#include <QtWidgets>
#include "Types.h"

class Produce:public QWidget
{
	Q_OBJECT
public:
	explicit Produce(QWidget *parent=0);
	const Package &getPackage();

private:
	Package items;
	void dropEvent(QDropEvent *e);
	void dragEnterEvent(QDragEnterEvent *e);
	
};

#endif // PRODUCE_H
