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
	const QRect &getRect() const {return rect;}
	const QPixmap &getPixmap() const {return pixmap;}
	
private:
	QRect rect;
	QPixmap pixmap;
	QVector<BitType> bitmap;
	Square square;

signals:
	void buffered();

public slots:
	void setRect(const QRect &rect);
	void setBitmap(const QVector<BitType> &_bitmap,const QRect &_rect);
};

#endif // BITMAP_H
