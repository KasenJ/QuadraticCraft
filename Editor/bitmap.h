#ifndef BITMAP_H
#define BITMAP_H
#include <QtCore>
#include <QString>
#include <QtSql>
struct combine{
    int first;
    int second;
    int third;
    int forth;
    int finish;
    QString occupation;
    combine(){}
    combine(int first, int second, int third, int forth, int finish, QString occupation)
    {
        this->first = first;
        this->second = second;
        this->third = third;
        this->forth = forth;
        this->finish = finish;
        this->occupation = occupation;
    }
};

class Bitmap
{
public:
    QVector<quint64> map;
    QVector<combine> CombineList;

    int height;
    int width;

    Bitmap();
    void setBitmap(int h,int w);
    void addCombineList(int index,int first,int second,int third,int forth,int finish,QString occupation);
    void deletecombinelist(int );
    quint64& at(int x,int y);
};

#endif // BITMAP_H
