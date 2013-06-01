#include "Login.h"

Login::Login(QWidget *parent) :
	QDialog(parent)
{
	setFixedSize(400,300);
	setWindowTitle(tr("Login"));
	address=new QLineEdit(this);
	address->setGeometry(100,120,200,20);
	address->setPlaceholderText(tr("Server IP"));
	username=new QLineEdit(this);
	username->setGeometry(100,160,200,20);
	username->setPlaceholderText(tr("Username"));
	password=new QLineEdit(this);
	password->setGeometry(100,200,200,20);
	password->setEchoMode(QLineEdit::Password);
	password->setPlaceholderText(tr("Password"));
	button=new QDialogButtonBox(this);
	button->setStandardButtons(QDialogButtonBox::Ok|QDialogButtonBox::Cancel);
	button->setGeometry(140,225,120,60);
	connect(button,&QDialogButtonBox::accepted,[this](){
		Share::server.setAddress(address->text());
		UserEvent event;
		event.setState(UserEvent::Login);
		event.setUsername(username->text());
		event.setPassword(password->text());
		Share::sendEvent(event);
		QTimer *timer=new QTimer(this);
		timer->setSingleShot(true);
		timer->start(1000);
		connect(timer,&QTimer::timeout,[this](){
			address->setPlaceholderText(tr("Connection Failed"));
			address->setText(QString());
			Share::server.clear();
		});
		connect(Share::socket,&Socket::getUserEvent,[this,timer](const UserEvent &event){
			timer->stop();
			if(event.getState()==UserEvent::Logged){
				accept();
			}
			else{
				password->setPlaceholderText(tr("Wrong Password"));
				password->setText(QString());
			}
		});
	});
	connect(button,&QDialogButtonBox::rejected,this,&QDialog::reject);
}

void Login::showEvent(QShowEvent *e)
{
	QPoint end=QApplication::desktop()->screenGeometry().center()-QPoint(200,150);
	QPoint sta=QPoint(end.x(),0);
	QPropertyAnimation *animation=new QPropertyAnimation(this,"pos",this);
	animation->setDuration(1200);
	animation->setStartValue(sta);
	animation->setEndValue(end);
	animation->setEasingCurve(QEasingCurve::OutBounce);
	animation->start();
	QWidget::showEvent(e);
}
