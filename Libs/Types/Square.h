#ifndef SQUARE_H
#define SQUARE_H

#include <QtGui>
#include <QtCore>

typedef quint8 BitType;

class Square:public QList<QPixmap>
{
public:
	enum{Black,White,Red};
	explicit Square();
};

#endif // SQUARE_H
