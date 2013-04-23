#include "Handler.h"

void Handler::DropEventHandle(const DropEvent &event,const QHostAddress &address)
{
    QSqlQuery query;
    query.prepare("SELECT Number FROM Own_package_cell WHERE PName=? AND Item=? AND Number>0");
    query.bindValue(0,userMap[address]);
    query.bindValue(1,event.getBit());
    query.exec();
    if(query.first()){
        int number=query.value("Number").toInt()-1;
        query.prepare("SELECT Type FROM Cube WHERE POSITION=?");
        query.bindValue(0,(event.getDrop().x()<<16)+event.getDrop().y());
        query.exec();
        if(query.first()){
            query.prepare("UPDATE Own_package_cell SET Number=? WHERE PName=? AND Item=? AND Number>0");
            query.bindValue(0,number);
            query.bindValue(1,userMap[address]);
            query.bindValue(2,event.getBit());
            query.exec();
            query.prepare("UPDATE Cube SET TYPE=? WHERE POSITION=?");
            query.bindValue(0,event.getBit());
            query.bindValue(1,(event.getDrop().x()<<16)+event.getDrop().y());
        }
    }
    qDebug()<<"Get DropEvent";
}
