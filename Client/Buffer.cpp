#include "Buffer.h"

Buffer::Buffer()
{
}

const QRect &Buffer::getRect() const
{
	return rect;
}

void Buffer::setRect(const QRect &rect)
{
	UpdateEvent event;
	event.setRect(this->rect);
	event.setBitmap(bitmap);
	this->rect=rect;
	bitmap.resize(rect.width()*rect.height());
	bitmap.fill(Bit::Black);
	update(event);
}

void Buffer::update(const UpdateEvent &event)
{
	bool flag=false;
	QRect receiveRect=event.getRect();
	QVector<BitType> receiveBitmap=event.getBitmap();
	if(rect.isNull()){
		rect=receiveRect;
		bitmap=receiveBitmap;
		flag=true;
	}
	else{
		int w=receiveRect.width();
		int rl=receiveRect.left();
		int rt=receiveRect.top();
		int cl=rect.left();
		int ct=rect.top();
		for(int i=0;i<receiveBitmap.size();++i){
			int x=i%w+rl,y=i/w+rt;
			if(rect.contains(x,y)){
				bitmap[x-cl+rect.width()*(y-ct)]=receiveBitmap[i];
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
			painter.drawPixmap((i%w)*50,(i/w)*50,square[bitmap[i]]);
		}
		painter.end();
		emit buffered();
	}
}
