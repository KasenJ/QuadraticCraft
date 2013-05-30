#include "Pack.h"

extern Square *square;

Pack::Pack(QWidget *parent):
	QWidget(parent)
{
	index=-1;
	isPop=isDrag=false;
	setAutoFillBackground(true);
	animation=new QPropertyAnimation(this,"pos",this);
	animation->setDuration(200);
	animation->setEasingCurve(QEasingCurve::OutCubic);
	produce=new Produce(this);
	produce->setGeometry(12.5,300,175,290);
	connect(produce,&Produce::produce,[this](Package d){emit send(d);});
}

void Pack::paintEvent(QPaintEvent *e)
{
	QPainter painter;
	painter.begin(this);
	painter.setPen(Qt::gray);
	int i,j,c=0;
	for(i=0;i<4;++i){
		for(j=0;j<3;++j){
			painter.drawRect(mapRect(i,j));
			if(c<package.size()){
				painter.drawPixmap(mapPosition(i,j),square->at(package[c].first));
				painter.drawText(mapPosition(i,j)+QPoint(4,47.5),QString("x%1").arg(package[c].second));
			}
			++c;
		}
	}
	if(index>=0){
		i=index/3;
		j=index%3;
		QPen pen;
		pen.setWidthF(2.5);
		pen.setColor(Qt::darkGray);
		pen.setJoinStyle(Qt::MiterJoin);
		painter.setPen(pen);
		painter.drawRect(mapRect(i,j));
	}
	painter.end();
	QWidget::paintEvent(e);
}

void Pack::mouseMoveEvent(QMouseEvent *e)
{
	if(isDrag){
		int i=getIndex(e->pos());
		if(i>=0){
			QMimeData *data=new QMimeData;
			data->setData("Item",Utils::toByteArray(package[i]));
			QDrag drag(this);
			drag.setMimeData(data);
			drag.setPixmap(square->at(package[i].first));
			drag.setHotSpot(e->pos()-mapPosition(i/3,i%3));
			drag.exec();
		}
	}
	else{
		isDrag=true;
	}
}

void Pack::mouseReleaseEvent(QMouseEvent *e)
{
	isDrag=false;
	index=getIndex(e->pos());
	update();
	QWidget::mouseReleaseEvent(e);
}

int Pack::getIndex(const QPoint &p) const
{
	int _index;
	bool flag=true;
	for(int i=0;i<4;++i){
		for(int j=0;j<3;++j){
			if(mapRect(i,j).contains(p)){
				_index=i*3+j;
				flag=_index>=package.size();
				break;
			}
		}
	}
	return flag?-1:_index;
}

QRect Pack::mapRect(int i,int j) const
{
	return QRect(mapPosition(i,j),QSize(50,50));
}

QPoint Pack::mapPosition(int i,int j) const
{
	return QPoint(12.5+62.5*j,15+65*i);
}

void Pack::pop()
{
	if(!isPop&&animation->state()==QAbstractAnimation::Stopped){
		animation->setStartValue(pos());
		animation->setEndValue(pos()-QPoint(200,0));
		animation->start();
		isPop=true;
	}
}

void Pack::push()
{
	if(isPop&&animation->state()==QAbstractAnimation::Stopped){
		animation->setStartValue(pos());
		animation->setEndValue(pos()+QPoint(200,0));
		animation->start();
		isPop=false;
	}
}

void Pack::setPackage(const Package &change)
{
	for(auto item:change){
		bool flag=true;
		for(auto &iter:package){
			if(iter.first==item.first){
				flag=false;
				iter.second+=item.second;
				if(iter.second==0){
					package.removeOne(iter);
					index=-1;
				}
				break;
			}
		}
		if(flag){
			package.append(item);
		}
	}
	update();
}
