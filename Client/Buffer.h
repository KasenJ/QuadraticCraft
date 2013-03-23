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
	const QRect &getRect() const;
	void setRect(const QRect &rect);
	const QPixmap &getPixmap(){return pixmap;}
	
private:
	QRect rect;
	QPixmap pixmap;
	QVector<BitType> bitmap;
	Square square;

signals:
	void buffered();

public slots:
	void update(const UpdateEvent &event);
};

#endif // BITMAP_H
