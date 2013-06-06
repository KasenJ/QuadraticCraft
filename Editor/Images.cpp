#include "Images.h"
#include "ui_Images.h"

ImageS::ImageS(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ImageS)
{
    ui->setupUi(this);
    load();
    qDebug()<<imageS.size();
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
        painter.drawPixmap(clown*60,row*60,50,50,imageS[i].pic);
        if(i == select){
            painter.drawRect(clown*60,row*60,50,50);
        }
        clown++;
    }
}

void ImageS::mousePressEvent(QMouseEvent *e)
{
    if(e->button()==Qt::LeftButton){
        auto cursor = e->pos();
        int x = cursor.rx();
        int y = cursor.ry()-45;
        int temp = x/60 + (y/60)*5;
        if(temp>=0 && temp< imageS.size())
            select = temp;
    }
    this->update();
}

QPixmap ImageS::atimageS(quint8 i)
{
    if(i==0){
        QPixmap p(50,50);
        p.fill(Qt::black);
        return p;
    }
    for(int j=0;j<imageS.size();j++){
        if(i == imageS[j].type)
            return imageS[j].pic;
    }
    return QPixmap();
}

void ImageS::on_pushButton_Load_clicked()
{
    load();
    this->update();
}

void ImageS::load()
{
    imageS = QVector<Access>(0);
    QSqlQuery query;
    query.exec("SELECT * FROM Bit");
    QByteArray b;
    int type;
    while(query.next()){
        type = query.value("Type").toInt();
        b = query.value("Texture").toByteArray();
        imageS.append( Access(type,Utils::fromByteArray<QPixmap>(b)) );
    }
}
