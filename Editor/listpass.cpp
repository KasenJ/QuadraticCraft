#include "listpass.h"
#include "ui_listpass.h"

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
