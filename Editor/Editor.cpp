#include <QtSql>
#include <QtCore>
#include "Types.h"

int main()
{
	if(!QFile::exists("Data.db")){
		auto data=QSqlDatabase::addDatabase("QSQLITE");
		data.setDatabaseName("Data.db");
		data.open();
		QSqlQuery query(data);
		data.transaction();
		query.exec("CREATE TABLE Player ( PName VARCHAR(20), TName VARCHAR(20), Occupation VARCHAR(20), Password VARCHAR(20), Position INTEGER, FOREIGN KEY(Position) REFERENCES Cube(Position), PRIMARY KEY(PName), UNIQUE(Position) );");
		query.exec("CREATE TABLE Cube ( Position INTEGER, Type INTEGER, PRIMARY KEY(Position) );");
		query.exec("CREATE TABLE Cell ( PName VARCHAR(20), Item INTEGER, Number INTEGER, PRIMARY KEY(PName, Item), FOREIGN KEY(PName) REFERENCES Player(PName) ON DELETE CASCADE );");
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
		data.commit();
		data.close();
	}
	return 0;
}
