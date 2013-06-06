#include "listpass.h"
#include "ui_listpass.h"
typedef quint8 BitType;
listPass::listPass(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::listPass)
{
    ui->setupUi(this);
    model = new QSqlTableModel(this);
    model->setTable("Bit");
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model->select();
    ui->tableView->setModel(model);
    ui->tableView->show();
}

listPass::~listPass()
{
    delete ui;
}

void listPass::on_pushButton_Submit_clicked()
{
    model->database().transaction();
    if (model->submitAll())
    {
        model->database().commit();
    } else {
        model->database().rollback();
        QMessageBox::warning(this,"DBE",model->lastError().text());
        model->revertAll();
    }
}

void listPass::on_pushButton_Add_clicked()
{
    // if(ui->lineEdit->text() != NULL){
    int rowNum = model->rowCount();
    int type = ui->lineEdit->text().toInt();
    QSqlRecord record = model->record();
    record.setValue("Type",type);
    // model->setRecord()
    qDebug()<<record<< model->insertRecord(rowNum,record);
    // model->insertRow(rowNum);
    // qDebug()<< model->setData(model->index(rowNum,0),type);
    qDebug()<< model->submitAll();
    // }
    // ui->lineEdit->setText("");
}

void listPass::on_pushButton_Delete_clicked()
{
    int curRow = ui->tableView->currentIndex().row();
    model->removeRow(curRow);
    model->submitAll();
}

void listPass::on_pushButton_pic_clicked()
{
    QString file = QFileDialog::getOpenFileName(this,"Select picS",QDir::currentPath(),"Images (*.png)");
    QPixmap pic = QPixmap(file);

    int type = model->index(ui->tableView->currentIndex().row(),0).data().toInt();
    QSqlQuery query;
    query.prepare("UPDATE Bit SET Texture = ? WHERE Type = ?");
    query.addBindValue(Utils::toByteArray<QPixmap>(pic));
    query.addBindValue(type);
    query.exec();
}

void listPass::on_pushButton_Info_clicked()
{
    QSqlQuery query;
    QString n= ui->lineEdit_2->text();
    QString d = ui->lineEdit_3->text();
    int type = model->index(ui->tableView->currentIndex().row(),0).data().toInt();
    query.prepare("UPDATE Bit SET Info = ? WHERE Type = ?");
    QByteArray a;
    QDataStream s(&a,QIODevice::WriteOnly);
    QHash <BitType,BitType> h;
    if(type == 128){
        h.insert(6+128,130);
        h.insert(7+128,129);
        h.insert(8+128,129);
        h.insert(9+128,129);
    }
    if(type == 129){
        h.insert(10+128,131);
        h.insert(12+128,131);
        h.insert(13+128,131);
        h.insert(11+128,132);
        h.insert(17+128,132);

    }
    if(type == 130){
        h.insert( 16+128,133);
        h.insert(18+128,133);
    }
    s<<n<<d<<h;
    query.addBindValue(a);
    query.addBindValue(type);
    query.exec();
}
