#include "Produce.h"

Produce::Produce(QWidget *parent):
	QWidget(parent)
{
	setAcceptDrops(true);
	setAutoFillBackground(true);
	QPalette palette;
	palette.setColor(QPalette::Window,Qt::white);
	setPalette(palette);
}

void Produce::dropEvent(QDropEvent *e)
{
	auto item=Utils::fromByteArray<Cell>(e->mimeData()->data("Item"));
	bool exists=false;
	for(Cell &cell:items){
		if(cell.first==item.first){
			cell.second=item.second;
			exists=true;
			break;
		}
	}
	if(!exists){
		items.append(item);
	}
}

void Produce::dragEnterEvent(QDragEnterEvent *e)
{
	if(e->mimeData()->hasFormat("Item")){
		e->acceptProposedAction();
	}
}
