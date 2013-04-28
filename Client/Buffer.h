#ifndef BITMAP_H
#define BITMAP_H

#include <QtGui>
#include <QtCore>
#include "Types.h"

class Buffer:public QObject
{
	Q_OBJECT
public:
	explicit Buffer();
	void draw(QPainter *painter);
	const QRect &getRect() const {return rect;}
	
private:
	QRect rect;
	QVector<BitType> bitmap;

public slots:
	void setRect(const QRect &rect);
	void setBitmap(const QVector<BitType> &_bitmap,const QRect &_rect);
};

#endif // BITMAP_H
