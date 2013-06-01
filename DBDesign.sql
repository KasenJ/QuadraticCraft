CREATE TABLE Player ( PName VARCHAR(20), Password VARCHAR(20), Occupation INTEGER, Position INTEGER, FOREIGN KEY(Position) REFERENCES Cube(Position), PRIMARY KEY(PName), UNIQUE(Position) );
CREATE TABLE Cube ( Position INTEGER, Type INTEGER, PRIMARY KEY(Position) );
CREATE TABLE Cell ( PName VARCHAR(20), Item INTEGER, Number INTEGER, PRIMARY KEY(PName, Item), FOREIGN KEY(PName) REFERENCES Player(PName) ON DELETE CASCADE ); 
CREATE TABLE Bit (Type INTEGER, Move BOOL, Take Bool, Info BLOB, Texture BLOB, PRIMARY KEY(Type) );
CREATE TABLE Formula (Composition INTEGER, Product INTEGER, Occupation INTEGER, UNIQUE(Composition, Occupation));
CREATE TABLE Event (Rect BLOB, Script BLOB);
CREATE TABLE Info (Name VARCHAR(20), Data BLOB, PRIMARY KEY(Name));