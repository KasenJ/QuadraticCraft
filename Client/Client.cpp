#include <QApplication>
#include "Login.h"
#include "Share.h"
#include "Interface.h"

int main(int argc, char *argv[])
{
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
	QString locale=QLocale::system().name();
	QTranslator myTrans;
	myTrans.load(locale+".qm");
	QTranslator qtTrans;
	qtTrans.load(locale+".qt.qm");
	a.installTranslator(&myTrans);
	a.installTranslator(&qtTrans);
	Socket socket;
	socket.setSendPort(12450);
	socket.setReceivePort(45012);
	Share::socket=&socket;
	Login login;
	login.show();
	Interface interface;
	if(login.exec()==QDialog::Accepted){
		interface.show();
		return a.exec();
	}
	else{
		return 0;
	}
}
