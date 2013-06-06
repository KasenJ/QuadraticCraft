#ifndef LISTPASS_H
#define LISTPASS_H
#include <QtCore>
#include <QtSql>
#include <QtWidgets>
#include <bitmap.h>
#include "Types.h"
namespace Ui {
class listPass;
}

class listPass : public QDialog
{
    Q_OBJECT

public:
    explicit listPass(QWidget *parent = 0);
    ~listPass();

private slots:
    void on_pushButton_Submit_clicked();

    void on_pushButton_Delete_clicked();

    void on_pushButton_Add_clicked();

    void on_pushButton_pic_clicked();

    void on_pushButton_Info_clicked();

private:
    Bitmap *map;
    Ui::listPass *ui;
    QSqlTableModel *model;
};

#endif // LISTPASS_H
