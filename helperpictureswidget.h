#ifndef HELPERPICTURESWIDGET_H
#define HELPERPICTURESWIDGET_H

#include <QWidget>

#include "level.h"

class HelperPicturesWidget
{
public:
	HelperPicturesWidget();

	static QString getStyleSheet(CellType type);

};

#endif // HELPERPICTURESWIDGET_H
