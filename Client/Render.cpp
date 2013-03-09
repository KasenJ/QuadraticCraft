#include "Render.h"

Render::Render(QWidget *parent) :
	QWidget(parent)
{
}

void Render::paintEvent(QPaintEvent *)
{
	QPainter painter;
	painter.begin(this);
	painter.end();
}

void Render::updateRect(const QRect &rect, const QList<quint8> &bitmap)
{

}
