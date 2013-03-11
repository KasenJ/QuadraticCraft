#include "Handler.h"

void Handler::UpdateEventHandle(const UpdateEvent &event,const QHostAddress &address)
{
	const QRect rect=event.getRect();
	QVector<BitType> bitmap;
	int x=rect.x(),y=rect.y(),w=rect.width(),h=rect.height();
	for(int i=0;i<h;i++){
		for(int j=0;j<w;j++){
			bitmap.append(((x+y+i+j)&1)+1);
		}
	}
	UpdateEvent reply;
	reply.setRect(rect);
	reply.setBitmap(bitmap);
	sendEvent(reply,address);
}
