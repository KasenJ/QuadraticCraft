#include "Render.h"

Render::Render(ImageS *i, Bitmap *b, QWidget *parent):
	QWidget(parent),i(i),b(b)
{
	setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
}

void Render::paintEvent(QPaintEvent *e)
{
	QPainter painter(this);
	for(int k=0;k<b->width;k++){
		for(int j=0;j<b->height;j++){
			painter.drawPixmap(k*50,j*50,i->atimageS(b->at(k,j)&0xFF));
		}
	}
	painter.end();
	QWidget::paintEvent(e);
}
