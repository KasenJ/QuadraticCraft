#include "Handler.h"

void Handler::UserEventHandle(const UserEvent &event,const QHostAddress &address)
{
	qDebug()<<"Get UserEvent";
	UserEvent reply;
	switch(event.getState()){
	case UserEvent::Login:{
		if(event.getUsername()=="root"){
			qDebug()<<"User"<<event.getUsername()<<"Logged";
			reply.setState(UserEvent::Logged);
			sendEvent(reply,address);
			UpdateEvent init;
			init.setRect(QRect(0,0,16,12));
			UpdateEventHandle(init,address);
		}
		else{
			reply.setState(UserEvent::Failed);
			sendEvent(reply,address);
		}
	}
	}
}
