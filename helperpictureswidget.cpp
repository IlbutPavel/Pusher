#include "helperpictureswidget.h"

HelperPicturesWidget::HelperPicturesWidget()
{

}

QString HelperPicturesWidget::getStyleSheet(CellType type)
{
	if (type == empty)
		return "QWidget { background-image: url(://pictures/empty.png); max-width: 30px; max-height: 30px; }";
	else if (type == wall)
		return "QWidget { background-image: url(://pictures/wall.png); max-width: 30px; max-height: 30px; }";
	else if (type == destination)
		return "QWidget { background-image: url(://pictures/destination.png); max-width: 30px; max-height: 30px; }";
	else if (type == box)
		return "QWidget { background-image: url(://pictures/box.png); max-width: 30px; max-height: 30px; }";
	else if (type == man)
		return "QWidget { background-image: url(://pictures/man.png); max-width: 30px; max-height: 30px; }";
	else if (type == destBox)
		return "QWidget { background-image: url(://pictures/dest_box.png); max-width: 30px; max-height: 30px;}";
	else if (type == destMan)
		return "QWidget { background-image: url(://pictures/man.png); max-width: 30px; max-height: 30px; }";
	else
		return "";
}
