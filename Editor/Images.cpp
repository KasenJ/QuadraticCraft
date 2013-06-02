#include "Images.h"
#include "ui_Images.h"

ImageS::ImageS(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ImageS)
{
    ui->setupUi(this);
    imageS = QVector<QPixmap>(0);
    load();
}

ImageS::~ImageS()
{
    delete ui;
}

void ImageS::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.translate(0,45);
    int row = 0,clown = 0;
    for(int i = 0;i < imageS.size();i++)
    {
        if(clown == 5){
            clown = 0;
            row++;
        }
        painter.drawPixmap(clown*60,row*60,50,50,imageS[i]);
        clown++;
    }
}

void ImageS::mousePressEvent(QMouseEvent *e)
{
    if(e->button()==Qt::LeftButton)
    {
        auto cursor = e->pos();
        int x = cursor.rx();
        int y = cursor.ry()-45;
        int temp = x/60 + (y/60)*5;
        if(temp>=0 && temp<imageS.size())
            _type = temp;
    }
}

QPixmap ImageS::atimageS(quint8 i)
{
    if(i==0){
        QPixmap p(50,50);
        p.fill(Qt::black);
        return p;
    }
    return imageS[i-1];
}

void ImageS::on_pushButton_Load_clicked()
{
    load();
    this->update();
}

void ImageS::load()
{
    imageS = QVector<QPixmap>(0);
    QSqlQuery query;
    query.exec("SELECT * FROM Bit");
    QByteArray b;
    int i = 0;
    while(query.next()){
        b = query.value("Texture").toByteArray();
        imageS.append(Utils::fromByteArray<QPixmap>(b));
        i++;
    }
}
