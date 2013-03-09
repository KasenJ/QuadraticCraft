#include "Exec.h"

Exec::Exec(QObject *parent):
	QObject(parent)
{
	QDialog login;
	login.setFixedSize(400,300);
	login.move(QApplication::desktop()->screenGeometry().center()-QPoint(200,150));
	login.setWindowTitle(tr("Login"));
	QDialogButtonBox button(&login);
	button.setStandardButtons(QDialogButtonBox::Ok|QDialogButtonBox::Cancel);
	button.setGeometry(140,250,120,40);
	QLineEdit address(&login);
	address.setGeometry(100,120,200,20);
	address.setPlaceholderText(tr("Server IP"));
	QLineEdit username(&login);
	username.setGeometry(100,160,200,20);
	username.setPlaceholderText(tr("Username"));
	QLineEdit password(&login);
	password.setGeometry(100,200,200,20);
	password.setPlaceholderText(tr("Password"));
	connect(&button,&QDialogButtonBox::accepted,&login,&QDialog::accept);
	connect(&button,&QDialogButtonBox::rejected,&login,&QDialog::reject);
	login.show();
	timer=new QTimer(this);
	timer->setSingleShot(true);
	if(login.exec()==QDialog::Accepted){
		server.setAddress(address.text());
		UserEvent event;
		event.setState(UserEvent::Login);
		event.setUsername(username.text());
		event.setPassword(password.text());
		port=12450;
		socket.bind(port);
		writeData(event.toByteArray());
		timer->start(1000);
		connect(timer,&QTimer::timeout,&QApplication::quit);
	}
	else{
		timer->start(0);
		connect(timer,&QTimer::timeout,&QApplication::quit);
	}
}

void Exec::bind(quint16 port)
{
	this->port=port;
	socket.bind(port);
	connect(&socket,&QUdpSocket::readyRead,this,&Exec::readData);
}

void Exec::readData()
{
	while(socket.hasPendingDatagrams()){
		QByteArray data;
		data.resize(socket.pendingDatagramSize());
		QHostAddress address;
		socket.readDatagram(data.data(),data.size(),&address);
	}
}

void Exec::writeData(const QByteArray &data)
{
	socket.writeDatagram(data,data.size(),server,port);
}
