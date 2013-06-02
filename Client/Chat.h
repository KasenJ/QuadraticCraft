#ifndef CHAT_H
#define CHAT_H

#include <QtCore>
#include <QtWidgets>
#include "Types.h"
#include "share.h"

class Chat:public QWidget
{
	Q_OBJECT
public:
	explicit Chat(QWidget *parent=0);
	~Chat();
	bool isPoped() const {return ioo!=0;}

private:
	int ioo;
	bool self;
	QTimer *timer;
	QTimer *delay;
	QLineEdit *line;
	QList<QStaticText> list;
	QGraphicsOpacityEffect *effect;
	void paintEvent(QPaintEvent *e);
	void resizeEvent(QResizeEvent *e);
	
public slots:
	void append(QString content);
	void fadeIn();
	void fadeOut();

};

#endif // CHAT_H
