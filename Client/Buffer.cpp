#include "Buffer.h"

extern Square *square;

Buffer::Buffer()
{
}

void Buffer::setRect(const QRect &rect)
{
	UpdateEvent event;
	event.setRect(this->rect);
	event.setBitmap(bitmap);
	this->rect=rect;
	bitmap.resize(rect.width()*rect.height());
	bitmap.fill(Bit::Black);
	setBitmap(event.getBitmap(),event.getRect());
}

void Buffer::setBitmap(const QVector<BitType> &_bitmap,const QRect &_rect)
{
	bool flag=false;
	if(rect.isNull()){
		rect=_rect;
		bitmap=_bitmap;
		flag=true;
	}
	else{
		int w=_rect.width();
		int rl=_rect.left();
		int rt=_rect.top();
		int cl=rect.left();
		int ct=rect.top();
		for(int i=0;i<_bitmap.size();++i){
			int x=i%w+rl,y=i/w+rt;
			if(rect.contains(x,y)){
				bitmap[x-cl+rect.width()*(y-ct)]=_bitmap[i];
				flag=true;
			}
		}
	}
	if(flag){
		QPainter painter;
		pixmap=QPixmap(rect.size()*50);
		painter.begin(&pixmap);
		int w=rect.width();
		for(int i=0;i<bitmap.size();++i){
			painter.drawPixmap((i%w)*50,(i/w)*50,square->at(bitmap[i]));
		}
		painter.end();
		emit buffered();
	}
}
