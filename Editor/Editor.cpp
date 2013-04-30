#include <QtSql>
#include <QtCore>
#include "Types.h"

int main()
{
	auto data=QSqlDatabase::addDatabase("QSQLITE");
	data.setDatabaseName("Data.db");
	data.open();
	QSqlQuery query(data);
	for(int i=0;i<50;i++){
		for(int j=0;j<50;j++){
			query.prepare("INSERT INTO Cube VALUES(?,?)");
			query.addBindValue(Utils::toInt(QPoint(i,j)));
			if(i==0||i==49||j==0||j==49){
				query.addBindValue(0);
			}
			else{
				query.addBindValue(((j/2+i/2)&1)+2);
			}
			query.exec();
		}
	}
	data.close();
	return 0;
}
