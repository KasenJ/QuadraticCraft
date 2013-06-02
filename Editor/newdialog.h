#ifndef NEWDIALOG_H
#define NEWDIALOG_H

#include <QDialog>
#include <mainwindow.h>
#include <bitmap.h>
namespace Ui {
class newDialog;
}

class newDialog : public QDialog
{
    Q_OBJECT

public:
    explicit newDialog(QWidget *parent = 0);
    ~newDialog();
    int getBitmapHeight();
    int getBitmapWidth();
private:
    Ui::newDialog *ui;
};

#endif // NEWDIALOG_H
