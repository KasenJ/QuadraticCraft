#include "bitmap.h"


Bitmap::Bitmap()
{
    CombineList = QVector<combine>(0);

    QSqlQuery query;

    query.exec("SELECT * FROM Formula");
    int i = 0;
    int comp;
    int temp[4] ;
    int result;
    QString occu;
    while(query.next()){
        comp = query.value("Composition").toInt();
        temp[3] = comp&0xFF;
        temp[2] = (comp&0xFFFF)>>8;
        temp[1] = (comp&0xFFFFFF)>>16;
        temp[0] = (comp&0xFFFFFFFF)>>24;
        result = query.value("Product").toInt();
        occu = query.value("Occupation").toString();
        addCombineList(i,temp[0],temp[1],temp[2],temp[3],result,occu);
        i++;
    }

    quint32 size,in,x,y;
    query.exec("SELECT Count(*) FROM Cube");
    if(query.next())
        size = query.value(0).toInt();

    if(size != 0){
        query.exec("SELECT * FROM Cube");
        height = sqrt(size);
        width = height;
        map = QVector<quint64>(height*width,0);
        while(query.next()){
            x = query.value("Position").toInt();
            y = x&0xFFFF;
            x = x>>16;
            in = query.value("Type").toInt();
            quint64& t = at(x,y);
            t = in;
        }
    }
    else
        setBitmap(0,0);
}

void Bitmap::setBitmap(int h,int w)
{
    map =  QVector<quint64>(h*w,0);
    height = h;
    width = w;
}

void Bitmap::addCombineList(int index,int first, int second, int third, int forth, int finish,QString occupation)
{
    if(index <= CombineList.size())
    {
        combine temp(first,second,third,forth,finish,occupation);
        if(index == CombineList.size())
            CombineList.append(temp);
        else
            CombineList[index] = temp;
    }
}

quint64& Bitmap::at(int x, int y)
{
    return map[y*width+x];
}


void Bitmap::deletecombinelist(int i)
{
    if(CombineList.size() != 0 && i <= CombineList.size()-1 && i >= 0)
        CombineList.remove(i);
}
