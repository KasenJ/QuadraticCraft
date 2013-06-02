#include "combinelist.h"
#include "ui_combinelist.h"

combineList::combineList(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::combineList)
{
    ui->setupUi(this);
}

combineList::~combineList()
{
    delete ui;
}

void combineList::setList(Bitmap* map)
{
    this->map = map;
    ui->tableWidget->setRowCount(map->CombineList.size());

    for(int i = 0;i < map->CombineList.size();i++)
    {
        ui->tableWidget->setItem(i,0,new QTableWidgetItem(QString::number(i+1)+"号配方"));
        ui->tableWidget->setItem(i,1,new QTableWidgetItem(QString::number(map->CombineList[i].first)));
        ui->tableWidget->setItem(i,2,new QTableWidgetItem(QString::number(map->CombineList[i].second)));
        ui->tableWidget->setItem(i,3,new QTableWidgetItem(QString::number(map->CombineList[i].third)));
        ui->tableWidget->setItem(i,4,new QTableWidgetItem(QString::number(map->CombineList[i].forth)));
        ui->tableWidget->setItem(i,5,new QTableWidgetItem(QString::number(map->CombineList[i].finish)));
        ui->tableWidget->setItem(i,6,new QTableWidgetItem(map->CombineList[i].occupation));
    }
}

void combineList::on_pushButton_Change_clicked()
{
    QSqlDatabase data = QSqlDatabase::addDatabase("QSQLITE");
    data.setDatabaseName("Data.db");
    data.open();
    QSqlQuery query(data);
    query.exec("DELETE FROM Formula");

    quint8 temp[4];
    for(int i = 0;i < map->CombineList.size();i++)
    {
        temp[0] = ui->tableWidget->item(i,1)->text().toInt();
        temp[1]= ui->tableWidget->item(i,2)->text().toInt() ;
        temp[2]= ui->tableWidget->item(i,3)->text().toInt() ;
        temp[3]= ui->tableWidget->item(i,4)->text().toInt();
        if(temp[0]<=temp[1]&&temp[1]<=temp[2]&&temp[2]<=temp[3]){
            int add = temp[0]; 
            add = (add<<8) +temp[1];
            add = (add<<8) +temp[2];
            add = (add<<8) +temp[3];
            qDebug()<<add;
            int fi = ui->tableWidget->item(i,5)->text().toInt();
            QString occu = ui->tableWidget->item(i,6)->text();
            map->addCombineList(i,temp[0],temp[1],temp[2],temp[3],fi,occu) ;

            query.prepare("INSERT INTO Formula VALUES(?,?,?)");
            query.addBindValue(add);
            query.addBindValue(fi);
            query.addBindValue(occu);
            query.exec();
        }
    }
    data.close();
    this->setList(map);
}

void combineList::on_pushButton_Add_clicked()
{
    int temp[4];
    int i = map->CombineList.size();
    temp[0] = ui->lineEdit_2->text().toInt();
    temp[1]= ui->lineEdit_3->text().toInt();
    temp[2]= ui->lineEdit_4->text().toInt();
    temp[3] = ui->lineEdit_5->text().toInt();
    if(temp[0]<=temp[1]&&temp[1]<=temp[2]&&temp[2]<=temp[3]){
        int add = temp[0];
        add = (add<<8) +temp[1];
        add = (add<<8) +temp[2];
        add = (add<<8) +temp[3];
        int fi = ui->lineEdit_6->text().toInt();
        QString p = ui->lineEdit_7->text();
        map->addCombineList(i,temp[0],temp[1],temp[2],temp[3],fi,p);
    }
    this->setList(map);
}

void combineList::on_pushButton_Delete_clicked()
{
    int currentRow = ui->tableWidget->currentRow();
    map->deletecombinelist(currentRow);
//    if(ui->lineEdit->text() != NULL)
//    {
//        map->deletecombinelist(ui->lineEdit->text().toInt()-1);
//        this->setList(map);
//    }
//    else
//    {
//        map->deletecombinelist(map->CombineList.size()-1);
//        this->setList(map);
//    }
    this->setList(map);
}
