#ifndef RENDER_H
#define RENDER_H

#include <QWidget>
#include "bitmap.h"
#include "Images.h"

class Render : public QWidget
{
	Q_OBJECT
public:
	explicit Render(ImageS *i,Bitmap *b,QWidget *parent=0);

private:
	ImageS *i;
	Bitmap *b;
	void paintEvent(QPaintEvent *e);
	
};

#endif // RENDER_H
