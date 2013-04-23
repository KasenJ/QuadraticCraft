#ifndef UTILS_H
#define UTILS_H

#include <QtCore>

namespace Utils
{
inline int toInt(QPoint point){return (point.x()<<16)+point.y();}
inline QPoint toPoint(int point){return QPoint(point>>16,point&0xFFFF);}
}

#endif // UTILS_H
