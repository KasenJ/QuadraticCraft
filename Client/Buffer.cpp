#include "Buffer.h"

extern Square *square;

Buffer::Buffer(QObject *parent):
	QObject(parent)
{
}

void Buffer::draw(QPainter *painter)
{
	QPoint t=rect.topLeft();
	int w=rect.width(),h=rect.height();
	for(int i=0;i<h;++i){
		for(int j=0;j<w;++j){
			QPoint p=QPoint(j,i);
			painter->drawPixmap(p*50,square->at(bitmap[Utils::toInt(p+t,buff)]));
		}
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
		buff=QRect(rect.topLeft()-QPoint(10,10),rect.bottomRight()+QPoint(10,10));
		blank.append(buff);
		bitmap.fill(Bit::Black,buff.width()*buff.height());
	}
	else{
		rect=_rect;
		QRect _buff=buff;
		if(rect.left()-2<buff.left()){
			buff.moveLeft(buff.left()-8);
			blank.append(QRect(QPoint(buff.left(),buff.top()),QPoint(_buff.left(),buff.bottom())));
		}
		if(rect.right()+2>buff.right()){
			buff.moveRight(buff.right()+8);
			blank.append(QRect(QPoint(_buff.right(),buff.top()),QPoint(buff.right(),buff.bottom())));
		}
		if(rect.top()-2<buff.top()){
			buff.moveTop(buff.top()-8);
			blank.append(QRect(QPoint(buff.left(),buff.top()),QPoint(buff.right(),_buff.top())));
		}
		if(rect.bottom()+2>buff.bottom()){
			buff.moveBottom(buff.bottom()+8);
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
		int s=r.width()*r.height();
		for(int j=0;i<_bitmap.size()&&j<s;++i,++j){
			QPoint p=Utils::toPoint(j,r)+r.topLeft();
			if(buff.contains(p)){
				bitmap[Utils::toInt(p,buff)]=_bitmap[i];
			}
		}
	}
}
