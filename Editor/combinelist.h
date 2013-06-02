#ifndef COMBINELIST_H
#define COMBINELIST_H
#include <bitmap.h>
#include <QDialog>
#include <QtSql>
namespace Ui {
class combineList;
}

class combineList : public QDialog
{
    Q_OBJECT

public:

    explicit combineList(QWidget *parent = 0);
    void setList(Bitmap* map);
    ~combineList();

private slots:
    void on_pushButton_Change_clicked();

    void on_pushButton_Add_clicked();

    void on_pushButton_Delete_clicked();

private:
    Bitmap* map;
    Ui::combineList *ui;
};

#endif // COMBINELIST_H
