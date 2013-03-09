#include "Square.h"

Square::Square()
{
	QString path(":Bitmap/Square/");
	QDir dir(path);
	for(auto &file:dir.entryList()){
		append(QPixmap(path+file));
	}
}
