#ifndef BITMAP_H
#define BITMAP_H

#include <QtGui>
#include <QtCore>
#include "Types.h"
#include "Share.h"

class Buffer:public QObject
{
	Q_OBJECT
public:
	explicit Buffer(QObject *parent=NULL);
	void draw(QPainter *painter);
	const QRect &getRect() const {return rect;}
	
private:
	QRect rect;
	QRect buff;
	QList<Role> roles;
	QVector<SquareType> bitmap;

public slots:
	void setRect(const QRect &_rect);
	void setRoles(const QList<Role> &_roles);
	void setBitmap(const Bitmap &_bitmap,const QRect &_rect);
	void setBitmap(const Bitmap &_bitmap,const QList<QRect> &_rects);
};

#endif // BITMAP_H
