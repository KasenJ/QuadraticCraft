#include "Buffer.h"

extern Square *square;

Buffer::Buffer(QObject *parent):
	QObject(parent)
{
}

void Buffer::draw(QPainter *painter)
{
	int w=rect.width();
	for(int i=0;i<bitmap.size();++i){
		painter->drawPixmap((i%w)*50,(i/w)*50,square->at(bitmap[i]));
	}
	for(const Role &role:roles){
		painter->drawPixmap((role.second-rect.topLeft())*50,square->at(role.first));
	}
}

QList<QRect> Buffer::takeBlank()
{
	QList<QRect> rects=blank;
	blank.clear();
	return rects;
}

void Buffer::setRect(const QRect &_rect)
{
	if(rect.isNull()){
		rect=_rect;
		buff=QRect(rect.topLeft()-QPoint(5,5),rect.bottomRight()+QPoint(5,5));
		blank.append(buff);
		bitmap.fill(Bit::Black,buff.width()*buff.height());
	}
	else{
		rect=_rect;
		QRect _buff=buff;
		if(rect.left()-2<buff.left()){
			buff.moveLeft(buff.left()-2);
			blank.append(QRect(QPoint(buff.left(),buff.top()),QPoint(_buff.left(),buff.bottom())));
		}
		if(rect.right()+2>buff.right()){
			buff.moveRight(buff.right()+2);
			blank.append(QRect(QPoint(_buff.right(),buff.top()),QPoint(buff.right(),buff.bottom())));
		}
		if(rect.top()-2<buff.top()){
			buff.moveTop(buff.top()-2);
			blank.append(QRect(QPoint(buff.left(),buff.top()),QPoint(buff.right(),_buff.top())));
		}
		if(rect.bottom()+2>buff.bottom()){
			buff.moveBottom(buff.bottom()+2);
			blank.append(QRect(QPoint(buff.left(),_buff.bottom()),QPoint(buff.right(),buff.bottom())));
		}
		if(buff!=_buff){
			QVector<BitType> _bitmap(bitmap);
			bitmap.resize(buff.width()*buff.height());
			bitmap.fill(Bit::Black);
			setBitmap(_bitmap,_buff);
		}
	}
}

void Buffer::setRoles(const QList<Role> &_roles)
{
	roles=_roles;
}

void Buffer::setBitmap(const QVector<BitType> &_bitmap, const QRect &_rect)
{
	QList<QRect> _rects={_rect};
	setBitmap(_bitmap,_rects);
}

void Buffer::setBitmap(const QVector<BitType> &_bitmap,const QList<QRect> &_rects)
{
	int i=0;
	for(const QRect &r:_rects){
		int w=r.width(),l=rect.left(),t=rect.top();
		for(;i<_bitmap.size();++i){
			int x=i%w+r.left(),y=i/w+r.right();
			if(buff.contains(x,y)){
				bitmap[x-l+buff.width()*(y-t)]=_bitmap[i];
			}
		}
	}
}
