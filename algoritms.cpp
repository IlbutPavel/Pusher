#include "algoritms.h"

#include <QMap>
#include <QDebug>

Algoritms::Algoritms(QObject *parent) : QObject(parent)
{

}

bool Algoritms::moveManForMouse(int xdest, int ydest, Level* level)
{
	bool successful = false;
	int xman = level->man_x;
	int yman = level->man_y;
	moveCell** moveField;
	moveField = new moveCell*[level->x];
	for (int i=0; i<level->x; i++)
		moveField[i] = new moveCell[level->y];


	QSet<QPair<int, int>> wasCell;					// close cell
	QMultiMap<int, QPair<int, int>> queMap;			// <distance <x_cell, y_cell>>

	queMap.insertMulti(0, QPair<int, int>(xman, yman));
	for (int dist=0; !queMap.isEmpty() && !successful; dist++)
	{
		for(auto it = queMap.begin(); it != queMap.end(); it = queMap.find(dist))
		{
			int i = it.value().first;
			int j = it.value().second;

			if (i == xdest && j == ydest)
			{
				qDebug() << "dist_end ================================================================== " << dist;

				successful = true;
				break;
			}
			wasCell.insert(it.value());
			queMap.remove(it.key(), it.value());

			//далее нужно развернуть ячейку
			if (i+1 <= level->x)
				if (level->field[i+1][j] == empty || level->field[i+1][j] == destination)
					if (!wasCell.contains(QPair<int, int>(i+1, j)))
						queMap.insertMulti(dist+1, QPair<int, int>(i+1, j));

			if (i-1 >= 0)
				if (level->field[i-1][j] == empty || level->field[i-1][j] == destination)
					if (!wasCell.contains(QPair<int, int>(i-1, j)))
						queMap.insertMulti(dist+1, QPair<int, int>(i-1, j));

			if (j+1 <= level->y)
				if (level->field[i][j+1] == empty || level->field[i][j+1] == destination)
					if (!wasCell.contains(QPair<int, int>(i, j+1)))
						queMap.insertMulti(dist+1, QPair<int, int>(i, j+1));

			if (j-1 >= 0)
				if (level->field[i][j-1] == empty || level->field[i][j-1] == destination)
					if (!wasCell.contains(QPair<int, int>(i, j-1)))
						queMap.insertMulti(dist+1, QPair<int, int>(i, j-1));

		}
	}




	for (int i=0; i<level->x; i++)
		delete moveField[i];
	delete  moveField;

	return successful;
}




