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
}

#endif // UTILS_H
