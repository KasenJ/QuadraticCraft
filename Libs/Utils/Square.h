#ifndef SQUARE_H
#define SQUARE_H

#include <QDir>
#include <QVector>
#include <QPixmap>

class Square:public QVector<QPixmap>
{
public:
	explicit Square();
};

#endif // SQUARE_H
