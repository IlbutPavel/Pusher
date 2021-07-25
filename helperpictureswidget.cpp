#include "helperpictureswidget.h"

HelperPicturesWidget::HelperPicturesWidget()
{

}

QString HelperPicturesWidget::getStyleSheet(CellType type)
{
	QString size = "max-width: " + QString::number(SIZE_CELL) + "px; max-height: " + QString::number(SIZE_CELL) + "px;";
	if (type == empty)
		return "QWidget { background-image: url(://pictures/empty.png); " + size + " }";
	else if (type == wall)
		return "QWidget { background-image: url(://pictures/wall.png); " + size + " }";
	else if (type == destination)
		return "QWidget { background-image: url(://pictures/destination.png); " + size + " }";
	else if (type == box)
		return "QWidget { background-image: url(://pictures/box.png); " + size + " }";
	else if (type == man)
		return "QWidget { background-image: url(://pictures/man.png); " + size + " }";
	else if (type == destBox)
		return "QWidget { background-image: url(://pictures/dest_box.png); " + size + " }";
	else if (type == destMan)
		return "QWidget { background-image: url(://pictures/man.png); " + size + " }";
	else
		return "";
}
