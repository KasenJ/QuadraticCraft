#include "Produce.h"

Produce::Produce(QWidget *parent):
	QFrame(parent)
{
	setAcceptDrops(true);
	setContextMenuPolicy(Qt::CustomContextMenu);
	setFrameStyle(QFrame::Plain|QFrame::StyledPanel);
	connect(this,&QFrame::customContextMenuRequested,[this](QPoint p){
		int i=(p.y()-10)/62.5;
		QMenu menu;
		if(i<items.size()){
			connect(menu.addAction(tr("Delete")),&QAction::triggered,[=](){
				items.removeAt(i);
				count.removeAt(i);
				update();
			});
		}
		connect(menu.addAction(tr("Clear")),&QAction::triggered,[this](){
			items.clear();
			count.clear();
			update();
		});
		connect(menu.addAction(tr("Produce")),&QAction::triggered,[this](){
			Package change=items;
			for(int i=0;i<change.size();++i){
				change[i].second=count[i];
			}
			items.clear();
			count.clear();
			update();
			ItemEvent e;
			e.setPackege(change);
			e.setOperation(ItemEvent::Produce);
			Share::sendEvent(e);
		});
		menu.exec(mapToGlobal(p));
	});
}

void Produce::dropEvent(QDropEvent *e)
{
	Cell item=Utils::fromByteArray<Cell>(e->mimeData()->data("Item"));
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
		count.append(item.second);
	}
	if(items.size()>4){
		items.removeFirst();
		count.removeFirst();
	}
	update();
}

void Produce::paintEvent(QPaintEvent *e)
{
	QPainter painter;
	painter.begin(this);
	int i=0;
	for(const Cell &item:items){
		painter.drawPixmap(10,10+i*62.5,Share::square->getPixmap(item.first));
		QString t=QString("%1%2");
		t=t.arg(QString("x%1").arg(count[i]),-6);
		t=t.arg(Share::square->getName(item.first));
		painter.drawText(65,40+i*62.5,t);
		++i;
	}
	painter.end();
	QFrame::paintEvent(e);
}

void Produce::wheelEvent(QWheelEvent *e)
{
	int i=(e->y()-10)/62.5;
	if(i<items.size()){
		int &n=count[i];
		n+=e->angleDelta().y()>0?1:-1;
		n=qBound(1,n,(int)items[i].second);
	}
	update();
	QFrame::wheelEvent(e);
}

void Produce::dragEnterEvent(QDragEnterEvent *e)
{
	if(e->mimeData()->hasFormat("Item")){
		e->acceptProposedAction();
	}
}
