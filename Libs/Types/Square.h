#ifndef SQUARE_H
#define SQUARE_H

#include <QDir>
#include <QList>
#include <QPixmap>

typedef quint8 BitType;

class Square:public QList<QPixmap>
{
public:
	enum{Black,White,Red};
	explicit Square();
};

#endif // SQUARE_H
