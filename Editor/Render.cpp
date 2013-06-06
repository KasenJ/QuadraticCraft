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
            BitType t;
            SquareType s=b->at(k,j);
            QList<QPixmap> l;
            do{
                t=s&0xFF;
                s=s>>8;
                l.prepend(i->atimageS(t));
            }
            while(t>=128);
            for(const QPixmap &p:l){
                painter.drawPixmap(k*50,j*50,p);
            }
		}
	}
	painter.end();
	QWidget::paintEvent(e);
}
