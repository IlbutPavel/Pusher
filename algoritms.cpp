#include "algoritms.h"

#include <QMap>
#include <QDebug>

Algoritms::Algoritms(Level* levelForSet, QObject *parent) : QObject(parent)
{
	level = levelForSet;

	moveField.resize(level->x);
	for (int i=0; i < level->x; i++)
		moveField[i].resize(level->y);
}

Algoritms::~Algoritms()
{

}

bool Algoritms::moveManForMouse(int xdest, int ydest, Level* level)
{
	int xman = level->man_x;
	int yman = level->man_y;

	for (int i = 0; i < level->x; i++)
	{
		for (int j = 0; j < level->y; j++)
		{
			moveField[i][j].isClosed = level->getFieldCell(i, j) != empty && level->getFieldCell(i, j) != destination;
			moveField[i][j].dist = -1;
		}
	}

	QMultiMap<int, QPair<int, int>> queMap;			// <distance <x_cell, y_cell>>
	queMap.insertMulti(0, QPair<int, int>(xman, yman));
	for (int dist=0; !queMap.isEmpty(); dist++)
	{
		while (!queMap.empty())
		{
			auto it = queMap.begin();
			if (it.key() != dist)
				break;

			int i = it.value().first;
			int j = it.value().second;
			moveField[i][j].dist = it.key();

			if (i == xdest && j == ydest)
				return true;

			moveField[i][j].isClosed = true;
			queMap.remove(it.key(), it.value());

			//далее нужно развернуть ячейку
			if (i+1 < level->x)
				if (!moveField[i+1][j].isClosed)
					queMap.insertMulti(dist+1, QPair<int, int>(i+1, j));

			if (i-1 >= 0)
				if (!moveField[i-1][j].isClosed)
					queMap.insertMulti(dist+1, QPair<int, int>(i-1, j));

			if (j+1 < level->y)
				if (!moveField[i][j+1].isClosed)
					queMap.insertMulti(dist+1, QPair<int, int>(i, j+1));

			if (j-1 >= 0)
				if (!moveField[i][j-1].isClosed)
					queMap.insertMulti(dist+1, QPair<int, int>(i, j-1));
		}
	}

//	QString showPath;																		//trace output
//	for (int j=0; j < level->y; j++)
//	{
//		showPath = "";
//		for (int i=0; i < level->x; i++)
//			if (moveField[i][j].dist == -1)
//				showPath += QString("      ").right(3);
//			else
//				showPath += ("      " + QString::number(moveField[i][j].dist)).right(3);
//		qWarning() << showPath;
//	}

	return false;
}

bool Algoritms::isCongratulation()
{
	for (int j=0; j < level->y; j++)
		for (int i=0; i < level->x; i++)
			if (level->getFieldCell(i, j) == box || level->getFieldCell(i, j) == destination)
				return false;

	return true;
}

//bool Algoritms::isCongratulation()
//{
//	for (int j=0; j < level->y; j++)
//		for (int i=0; i < level->x; i++)
//			if (level->getFieldCell(i, j) == destBox)
//				return true;

//	return false;
//}


