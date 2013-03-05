#include <QCoreApplication>
#include "Exec.h"

int main(int argc, char *argv[])
{
	QCoreApplication a(argc, argv);
	Exec exec;
	exec.bind(12450);
	return a.exec();
}
