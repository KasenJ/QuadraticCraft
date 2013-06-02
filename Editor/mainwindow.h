#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <combinelist.h>
#include <listpass.h>
#include <QPicture>
#include <QtGui>
#include <QMainWindow>
#include <bitmap.h>
#include <QPaintEvent>
#include <QKeyEvent>
#include <QMouseEvent>
#include <QString>
#include "bitmap.h"
#include <QPointer>
#include <QPicture>
#include <newdialog.h>
#include <QString>
#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <QtCore>
#include <QtSql>
#include "Images.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void keyPressEvent(QKeyEvent *);
    void mousePressEvent(QMouseEvent *);
    void paintEvent(QPaintEvent *);
    void mouseMoveEvent(QMouseEvent *);
    void setpic(int,int);

    void doNew();

    void openBitmap(QString s);
    void saveBitmap(QString s2);

private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();

    void on_action_triggered();

    void on_actionSetpass_triggered();
    void on_actionCombinelist_triggered();
    void on_pushButton_3_clicked();

private:
    Ui::MainWindow *ui;
    quint8 type;
    Bitmap Map;
    bool paint_true = true;
    ImageS *imageshow;
    QPoint dragPosition;
};

#endif // MAINWINDOW_H

