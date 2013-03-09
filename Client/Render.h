#ifndef RENDER_H
#define RENDER_H

#include <QtGui>
#include <QtCore>
#include <QtWidgets>

class Render:public QWidget
{
	Q_OBJECT
public:
	explicit Render(QWidget *parent = 0);
	
private:
	QRect bufferRect;
	QPoint centerPoint;

	void paintEvent(QPaintEvent *);

public slots:
	void updateRect(const QRect &rect,const QList<quint8> &bitmap);
};

#endif // RENDER_H
