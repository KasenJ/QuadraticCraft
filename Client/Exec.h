#ifndef EXEC_H
#define EXEC_H

#include <QObject>
#include <QUdpSocket>

class Exec:public QObject
{
	Q_OBJECT
public:
	explicit Exec(QObject *parent=0);

private:
	quint16 port;
	QUdpSocket socket;

signals:
	void dataReceived(const QByteArray &data,const QHostAddress &address);

public slots:
	void bind(quint16 port=0);
	void readData();
	void writeData(const QByteArray &data,const QHostAddress &address);
};

#endif // EXEC_H
