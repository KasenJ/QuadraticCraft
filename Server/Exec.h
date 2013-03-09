#ifndef EXEC_H
#define EXEC_H

#include <QtCore>
#include <QtNetwork>
#include "../Libs/Types.h"

class Exec:public QObject
{
	Q_OBJECT
public:
	explicit Exec(QObject *parent=0);
	inline Exec *exec(){return this;}

private:
	quint16 port;
	QUdpSocket socket;

public slots:
	void bind(quint16 port=0);
	void readData();
	void writeData(const QByteArray &data,const QHostAddress &address);
};

#endif // EXEC_H
