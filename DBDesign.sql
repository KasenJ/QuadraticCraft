CREATE TABLE Player ( PName VARCHAR(20), TName VARCHAR(20), Occupation VARCHAR(20), Password VARCHAR(20), Position INTEGER, FOREIGN KEY(Position) REFERENCES Cube(Position), PRIMARY KEY(PName), UNIQUE(Position) );
CREATE TABLE Cube ( Position INTEGER, Type INTEGER, PRIMARY KEY(Position) );
CREATE TABLE Cell ( PName VARCHAR(20), Item INTEGER, Number INTEGER, PRIMARY KEY(PName, Item), FOREIGN KEY(PName) REFERENCES Player(PName) ON DELETE CASCADE ); 
CREATE TABLE Access (Type INTEGER, Control BOOL, PRIMARY KEY(Type) );
CREATE TABLE Formula (Composition INTEGER, Product INTEGER, Priority INTEGER, PRIMARY KEY(Composition));
CREATE TABLE Event (Rect BLOB, Dialog BLOB, Motion BLOB);
