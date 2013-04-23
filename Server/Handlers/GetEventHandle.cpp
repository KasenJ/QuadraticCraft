#include "Handler.h"

void Handler::GetEventHandle(const GetEvent &event,const QHostAddress &address)
{
	qDebug()<<"Get GetEvent";
    QSqlQuery query;
    query.prepare("SELECT Type FROM Cube Where Position=?");
    query.addBindValue((event.getGet().x()<<16)+event.getGet().y());
    query.exec();
    if(query.first()){
        int type=query.record().indexOf("Type");
        query.prepare("SELECT * FROM Own_package_cell WHERE PName=? AND Item=?");
        query.addBindValue(userMap[address]);
        query.addBindValue(type);
        query.exec();
        if(query.first()){
            int number=query.record().indexOf("Number");
            query.prepare("UPDATE Own_package_cell SET Number=? WHERE PName=? AND Item=?");
            query.addBindValue(++number);
            query.addBindValue(userMap[address]);
            query.addBindValue(type);
            query.exec();
        }
        else{
            query.prepare("INSERT INTO Own_package_cell (PName,Item,Number)""VALUES(?,?,?)");
            query.addBindValue(userMap[address]);
            query.addBindValue(type);
            query.addBindValue(1);
            query.exec();
        }
        query.prepare("UPDATE Cube SET Type=? Where Position=?");
        query.addBindValue(type>>8);
        query.addBindValue((event.getGet().x()<<16)+event.getGet().y());
        query.exec();

    }
}
