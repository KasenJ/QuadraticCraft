#ifndef UTILS_H
#define UTILS_H

#include <QtCore>

namespace Utils
{
inline int toInt(QPoint point){return (point.x()<<16)+point.y();}
inline QPoint toPoint(int point){return QPoint(point>>16,point&0xFFFF);}

template <class T>
inline QByteArray toByteArray(const T &t)
{
	QByteArray d;
	QDataStream s(&d,QIODevice::WriteOnly);
	s<<t;
	return d;
}

template <class T>
inline T fromByteArray(const QByteArray &d)
{
	QDataStream s(d);
	T t;
	s>>t;
	return t;
}

template<class Func>
void delayExec(int time,Func func)
{
	QTimer *delay=new QTimer;
	delay->setSingleShot(true);
	delay->start(time);
	delay->connect(delay,&QTimer::timeout,func);
	delay->connect(delay,&QTimer::timeout,[delay]{delay->deleteLater();});
}
}

#endif // UTILS_H
