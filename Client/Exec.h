#ifndef EXEC_H
#define EXEC_H

#include <QtGui>
#include <QtCore>
#include <QtWidgets>
#include <QtNetwork>
#include "../Libs/Types.h"

class Exec:public QObject
{
	Q_OBJECT
public:
	explicit Exec(QObject *parent=0);
	inline Exec *exec(){return this;}

private:
	QTimer *timer;
	quint16 port;
	QUdpSocket socket;
	QHostAddress server;

public slots:
	void bind(quint16 port=0);
	void readData();
	void writeData(const QByteArray &data);
};

#endif // EXEC_H
