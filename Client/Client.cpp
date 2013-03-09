#include <QApplication>
#include "Login.h"
#include "Interface.h"

int main(int argc, char *argv[])
{
	QApplication::setStyle("Fusion");
	QApplication a(argc, argv);
	Socket socket;
	socket.setSendPort(12450);
	socket.setReceivePort(45012);
	Login login;
	login.setSocket(&socket);
	login.show();
	Interface interface;
	interface.setSocket(&socket);
	if(login.exec()==QDialog::Accepted){
		interface.setServer(login.getServer());
		interface.show();
		return a.exec();
	}
	else{
		return 0;
	}
}
