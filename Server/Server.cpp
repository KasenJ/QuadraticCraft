#include <QCoreApplication>
#include "Types.h"
#include "Handler.h"

int main(int argc, char *argv[])
{
	QCoreApplication a(argc, argv);
	Socket socket;
	socket.setSendPort(45012);
	socket.setReceivePort(12450);
	Handler handler;
	handler.setSocket(&socket);
	return a.exec();
}
