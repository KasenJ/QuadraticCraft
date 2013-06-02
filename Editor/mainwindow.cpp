#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    imageshow = new ImageS(ui->dockWidget);
    setMouseTracking(true);
	imageshow->setGeometry(0,80,300,600);
	auto sc=new QScrollArea(this);
	render=new Render(imageshow,&Map);
	sc->setWidget(render);
	setCentralWidget(sc);
}

MainWindow::~MainWindow()
{
    delete ui;
    imageshow->close();
}

void MainWindow::keyPressEvent(QKeyEvent *e)
{
    if(e->key() == Qt::Key_E)
    {
        auto cursor = mapFromGlobal(QCursor::pos());
        int x = (cursor.rx()-300)/50;
        int y = (cursor.ry()-35)/50;
        if(x>=0&&y>=0&&x<=Map.width&&y<=Map.height){
            if(cursor.rx()-300>0&&cursor.ry()-35>0){
            }
        }
    }
}

void MainWindow::mousePressEvent(QMouseEvent *e)
{
    if(e->button()==Qt::LeftButton)
    {
        auto cursor = mapFromGlobal(QCursor::pos());
        int x = (cursor.rx()-300)/50;
        int y = (cursor.ry()-35)/50;
        if(x>=0&&y>=0&&x<=Map.width&&y<=Map.height){
            if(cursor.rx()-300>0&&cursor.ry()-35>0)
                setpic(x,y);
        }
        this->update();
    }
    if(e->button() == Qt::RightButton){
		dragPosition = render->pos()-e->pos();
        e->accept();
    }
}
void MainWindow::setpic(int x,int y)
{
    type = imageshow->getType();
    int painter_height =ui->lineEdit->text().toInt();
    int painter_width = ui->lineEdit_2->text().toInt();
    for(int i = 0;i < painter_width; i++)
    {
        if(x+i==Map.width||x+i<0)    break;
        for(int j = 0;j < painter_height; j++)
        {
            if(y+j==Map.height||y+j<0)    break;
            quint64& temp = Map.at( x+i, y+j);
            if(paint_true){
                if(temp<=0XFFFFFFFFFFFFFF)
                    temp = (temp<<8)+type;
            }
            else
                temp = temp>>8;
        }
    }
}

void MainWindow::on_pushButton_clicked()
{
    paint_true = true;
}

void MainWindow::on_pushButton_2_clicked()
{
    paint_true = false;
}

void MainWindow::doNew()
{
    newDialog creatnew;
    if(creatnew.exec()== QDialog::Accepted)
    {
        int height;
        height = creatnew.getBitmapHeight();
        int width;
        width  = creatnew.getBitmapWidth();
        Map.setBitmap(height,width);
		render->resize(height*50,width*50);
        update();

        Map.CombineList.clear();
        Map.CombineList = QVector<combine>(0);
    }
}

void MainWindow::on_action_triggered()
{
    doNew();
}

void MainWindow::on_actionSetpass_triggered()
{
    listPass lp;

    if(lp.exec()== listPass::Accepted)
        lp.show();
}

void MainWindow::on_actionCombinelist_triggered()
{
    combineList c;
    c.setList(&Map);

    if(c.exec()== combineList::Accepted)
        c.show();
}

void MainWindow::on_pushButton_3_clicked()
{
    QSqlQuery query;
    QSqlDatabase data=QSqlDatabase::database();
    data.open();
    data.transaction();
    query.exec("DELETE FROM Cube");
    for(int i=0; i < Map.width; i++)
    {
        query.prepare("INSERT INTO Cube VALUES(?,?)");
        QVariantList types,positions;
        for(int j=0; j < Map.height; j++)
        {
            types << (i<<16)+j;
            if(i==0||j==0||i==Map.width-1||j==Map.height-1)
                positions << 0;
            else
                positions << Map.at(i,j);
        }
        query.addBindValue(types);
        query.addBindValue(positions);
        query.execBatch();
    }
    data.commit();
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    if (event->buttons() & Qt::RightButton) {
		render->move(dragPosition+event->pos());
        event->accept();
    }
}
