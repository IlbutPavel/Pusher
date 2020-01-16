#include "level.h"


Level::Level(int xx, int yy, QObject* parent) : QObject(parent)
{
	x = xx;
	y = yy;

	field.resize(x);
	for (int i=0; i<x; i++)
		field[i].resize(y);
}

Level::Level(Level* needCopy, QObject* parent) : QObject(parent)
{
	x = needCopy->x;
	y = needCopy->y;

	man_x = needCopy->man_x;
	man_y = needCopy->man_y;

	field = needCopy->field;
}
