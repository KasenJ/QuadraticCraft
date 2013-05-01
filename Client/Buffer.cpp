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
}

void Buffer::setRect(const QRect &rect)
{
	QList<QRect> _rects={this->rect};
	QVector<BitType> _bitmap(bitmap);
	this->rect=rect;
	bitmap.resize(rect.width()*rect.height());
	bitmap.fill(Bit::Black);
	setBitmap(_bitmap,_rects);
}

void Buffer::setBitmap(const QVector<BitType> &_bitmap,const QList<QRect> &_rects)
{
	if(rect.isNull()){
		for(auto &_rect:_rects){
			rect=rect.isNull()?_rect:rect.united(_rect);
		}
		bitmap.fill(Bit::Black,rect.width()*rect.height());
	}
	int i=0;
	for(auto &_rect:_rects){
		int w=_rect.width();
		int rl=_rect.left();
		int rt=_rect.top();
		int cl=rect.left();
		int ct=rect.top();
		for(;i<_bitmap.size();++i){
			int x=i%w+rl,y=i/w+rt;
			if(rect.contains(x,y)){
				bitmap[x-cl+rect.width()*(y-ct)]=_bitmap[i];
			}
		}
	}
}
