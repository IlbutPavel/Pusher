#include "level.h"


Level::Level(int xx, int yy, QObject* parent) : QObject(parent)
{
	x = xx;
	y = yy;

	field = new CellType*[x];
	for (int i=0; i<x; i++)
	{
		field[i] = new CellType[y];
	}
}

Level::Level(Level* needCopy)
{
	x = needCopy->x;
	y = needCopy->y;

	man_x = needCopy->man_x;
	man_y = needCopy->man_y;

	field = new CellType*[x];
	for (int i=0; i<x; i++)
	{
		field[i] = new CellType[y];
	}

	for (int j=0; j<y; j++)
		for (int i=0; i<x; i++)
			field[i][j] = needCopy->field[i][j];
}
