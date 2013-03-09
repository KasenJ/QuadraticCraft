#include "Login.h"

Login::Login(QWidget *parent) :
	QDialog(parent)
{
	setFixedSize(400,300);
	setWindowTitle(tr("Login"));
	move(QApplication::desktop()->screenGeometry().center()-QPoint(200,150));
	QDialogButtonBox *button=new QDialogButtonBox(this);
	button->setStandardButtons(QDialogButtonBox::Ok|QDialogButtonBox::Cancel);
	button->setGeometry(140,250,120,40);
	QLineEdit *address=new QLineEdit(this);
	address->setGeometry(100,120,200,20);
	address->setPlaceholderText(tr("Server IP"));
	QLineEdit *username=new QLineEdit(this);
	username->setGeometry(100,160,200,20);
	username->setPlaceholderText(tr("Username"));
	QLineEdit *password=new QLineEdit(this);
	password->setGeometry(100,200,200,20);
	password->setEchoMode(QLineEdit::Password);
	password->setPlaceholderText(tr("Password"));
	connect(button,&QDialogButtonBox::accepted,[=](){
		server.setAddress(address->text());
		UserEvent event;
		event.setState(UserEvent::Login);
		event.setUsername(username->text());
		event.setPassword(password->text());
		socket->sendEvent(event,server);
		QTimer *timer=new QTimer(this);
		timer->setSingleShot(true);
		timer->start(1000);
		connect(timer,&QTimer::timeout,[=](){
			address->setPlaceholderText(tr("Connection Failed"));
			address->setText(QString());
			server.clear();
		});
		connect(socket,&Socket::getUserEvent,[=](const UserEvent &event){
			if(event.getState()==UserEvent::Logged){
				timer->stop();
				accept();
			}
			else{
				timer->stop();
				password->setPlaceholderText(tr("Wrong Password"));
				password->setText(QString());
			}
		});
	});
	connect(button,&QDialogButtonBox::rejected,this,&QDialog::reject);
}

void Login::setSocket(Socket *socket)
{
	this->socket=socket;
}

const QHostAddress &Login::getServer() const
{
	return server;
}
