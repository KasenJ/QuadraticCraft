#include <QApplication>
#include "Login.h"
#include "Interface.h"

int main(int argc, char *argv[])
{
	QTranslator myTrans;
	myTrans.load("zh_CN.qm",":/Trans/");
	QTranslator qtTrans;
	qtTrans.load("zh_CN.qt.qm",":/Trans/");
#ifdef Q_OS_WIN
	QFont font("微软雅黑");
	font.setPointSize(9);
	QApplication::setFont(font);
#endif
#ifdef Q_OS_LINUX
	QFont font("文泉驿正黑");
	font.setPointSize(9);
	QApplication::setFont(font);
#endif
	QApplication::setStyle("Fusion");
	QApplication a(argc, argv);
	a.installTranslator(&myTrans);
	a.installTranslator(&qtTrans);
	Socket socket;
	socket.setSendPort(12450);
	socket.setReceivePort(45012);
	int state=0;
	while(state==0){
		Login login;
		login.setSocket(&socket);
		login.show();
		Interface interface;
		interface.setSocket(&socket);
		if(login.exec()==QDialog::Accepted){
			interface.setServer(login.getServer());
			interface.show();
			state=a.exec();
		}
		else{
			state=-1;
		}
	}
	return state>=0?state:0;
}
