#ifndef BITMAP_H
#define BITMAP_H

#include <QtGui>
#include <QtCore>
#include "Types.h"
#include "Square.h"

class Buffer:public QObject
{
	Q_OBJECT
public:
	explicit Buffer(QObject *parent=NULL);
	void draw(QPainter *painter);
	const QRect &getRect() const {return rect;}
	QList<QRect> takeBlank();
	
private:
	QRect rect;
	QRect buff;
	QList<Role> roles;
	QList<QRect> blank;
	QVector<BitType> bitmap;

public slots:
	void setRect(const QRect &_rect);
	void setRoles(const QList<Role> &_roles);
	void setBitmap(const QVector<BitType> &_bitmap,const QRect &_rect);
	void setBitmap(const QVector<BitType> &_bitmap,const QList<QRect> &_rects);
};

#endif // BITMAP_H
