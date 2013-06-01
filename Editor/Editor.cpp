#include <QtSql>
#include <QtGui>
#include <QtCore>
#include <QtWidgets>
#include "Types.h"

int main(int argc,char ** argv)
{
	QApplication a(argc,argv);
	if(!QFile::exists("Data.db")){
		auto data=QSqlDatabase::addDatabase("QSQLITE");
		data.setDatabaseName("Data.db");
		data.open();
		QSqlQuery query(data);
		data.transaction();
		query.exec("CREATE TABLE Player ( PName VARCHAR(20), Password VARCHAR(20), Occupation INTEGER, Position INTEGER, FOREIGN KEY(Position) REFERENCES Cube(Position), PRIMARY KEY(PName), UNIQUE(Position) );");
		query.exec("CREATE TABLE Cube ( Position INTEGER, Type INTEGER, PRIMARY KEY(Position) );");
		query.exec("CREATE TABLE Cell ( PName VARCHAR(20), Item INTEGER, Number INTEGER, PRIMARY KEY(PName, Item), FOREIGN KEY(PName) REFERENCES Player(PName) ON DELETE CASCADE );");
		query.exec("CREATE TABLE Bit (Type INTEGER, Move BOOL, Take Bool, Info BLOB, Texture BLOB, PRIMARY KEY(Type) );");
		query.exec("CREATE TABLE Formula (Composition INTEGER, Product INTEGER, Occupation INTEGER, UNIQUE(Composition, Occupation));");
		query.exec("CREATE TABLE Event (Rect BLOB, Script BLOB);");
		query.exec("CREATE TABLE Info (Name VARCHAR(20), Data BLOB, PRIMARY KEY(Name));");
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
		query.prepare("INSERT INTO Bit (Type,Move,Take,Texture) VALUES(0,0,1,?)");
		query.addBindValue(Utils::toByteArray(QPixmap("000.png")));
		query.exec();
		query.prepare("INSERT INTO Bit (Type,Move,Take,Texture) VALUES(1,0,1,?)");
		query.addBindValue(Utils::toByteArray(QPixmap("001.png")));
		query.exec();
		query.prepare("INSERT INTO Bit (Type,Move,Take,Texture) VALUES(2,1,1,?)");
		query.addBindValue(Utils::toByteArray(QPixmap("002.png")));
		query.exec();
		query.prepare("INSERT INTO Bit (Type,Move,Take,Texture) VALUES(3,1,1,?)");
		query.addBindValue(Utils::toByteArray(QPixmap("003.png")));
		query.exec();
		query.prepare("INSERT INTO Bit (Type,Move,Take,Texture) VALUES(128,0,0,?)");
		query.addBindValue(Utils::toByteArray(QPixmap("128.png")));
		query.exec();

		query.exec("INSERT INTO Formula VALUES (515,1,128)");

		ScriptEvent initScript;
		Dialog initDialogs;
		initDialogs.append(QPair<QString,quint32>("你想明白生命的意义吗？",2000));
		initDialogs.append(QPair<QString,quint32>("你想真正的·······活着吗？",2000));
		initScript.setDialog(initDialogs);
		query.prepare("INSERT INTO Event VALUES(?,?)");
		query.addBindValue(Utils::toByteArray(QRect(0,0,5,5)));
		query.addBindValue(initScript.toByteArray());
		query.exec();

		query.prepare("INSERT INTO Info VALUES(?,?)");
		query.addBindValue("Rect");
		query.addBindValue(Utils::toByteArray(QRect(1,1,48,48)));
		query.exec();
		data.commit();
		data.close();
	}
	return 0;
}
