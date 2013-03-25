#include "Handler.h"

void Handler::UpdateEventHandle(const UpdateEvent &event,const QHostAddress &address)
{
	qDebug()<<"Get UpdateEvent";
	const QRect rect=event.getRect();
	QVector<BitType> bitmap;
	int x=rect.x(),y=rect.y(),w=rect.width(),h=rect.height();
	for(int i=0;i<h;i++){
		for(int j=0;j<w;j++){
			bitmap.append((((x+j)/2+(y+i)/2)&1)+3);
		}
	}
	UpdateEvent reply;
	reply.setRect(rect);
	reply.setBitmap(bitmap);
	sendEvent(reply,address);
}
