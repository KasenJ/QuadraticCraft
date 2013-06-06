#ifndef RENDER_H
#define RENDER_H

#include <QWidget>
#include "bitmap.h"
#include "Images.h"

typedef quint8 BitType;
typedef quint64 SquareType;

class Render : public QWidget
{
	Q_OBJECT
public:
    explicit Render(ImageS *i,Bitmap *b,QWidget *parent=0);

private:
	ImageS *i;
	Bitmap *b;
    void (*funptr)(int ,int);
    void paintEvent(QPaintEvent *e);
};

#endif // RENDER_H
