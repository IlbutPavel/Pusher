#include "level.h"


Level::Level(int nn, int xx, int yy, QObject* parent) : QObject(parent)
{
	n = nn;
	x = xx;
	y = yy;

	field.resize(x);
	for (int i=0; i<x; i++)
		field[i].resize(y);
}

Level::Level(Level* needCopy, QObject* parent) : QObject(parent)
{
	n = needCopy->n;
	x = needCopy->x;
	y = needCopy->y;

	man_x = needCopy->man_x;
	man_y = needCopy->man_y;

	field = needCopy->field;
}

CellType Level::getFieldCell(int i, int j)
{
	return field[i][j];
}

void Level::setFieldCell(int i, int j, CellType cell)
{
	field[i][j] = cell;
	for (auto& observer: observers)
	{
		observer->redrawPictureWidget(i, j, cell);
	}
}

void Level::addObserver(Observer* observer)
{
	observers.append(observer);
}

void Level::setFinishPlay()
{
	for (auto& observer: observers)
	{
		observer->finishPlay();
	}
}
