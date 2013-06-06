#ifndef IMAGES_H
#define IMAGES_H

#include <QWidget>
#include <QtCore>
#include <QDir>
#include <QVector>
#include <QPixmap>
#include <QPainter>
#include <QMouseEvent>
#include <QFileDialog>
#include <QtSql>
#include "Types.h"
namespace Ui {
class ImageS;
}
struct Access{
    int type;
    QPixmap pic;
    Access(){}
    Access(int t,QPixmap p){
        type =t;    pic = p;
    }
};

class ImageS : public QWidget
{
    Q_OBJECT

public:
    explicit ImageS(QWidget *parent = 0);
    ~ImageS();
    int getType(){return imageS[select].type;}
    void mousePressEvent(QMouseEvent *);
    QPixmap atimageS(quint8 i);

private slots:

    void on_pushButton_Load_clicked();

private:
    Ui::ImageS *ui;
    QVector<Access> imageS;
    int select = 0;
    void paintEvent(QPaintEvent *e);
    void load();
};

#endif // IMAGES_H
