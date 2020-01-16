#include "maps.h"

#include <QDebug>

Maps::Maps(QObject *parent) : QObject(parent)
{
	QFile* file = new QFile("://maps/sokoban-maps-60-plain.txt", this);
	if (!file->open(QIODevice::ReadOnly | QIODevice::Text))
	{
		qDebug() << "file sokoban-maps-60-plain.txt don't open";
	}
	else
	{
		while (true)
		{
			file->readLine();												// empty line
			file->readLine();												// *******************
			int n = file->readLine().trimmed().mid(6).toInt();				// number of map
			file->readLine();												// File offset: 148C, DS:00FC, table offset: 0000
			int x = file->readLine().trimmed().mid(8).toInt();				// x
			int y = file->readLine().trimmed().mid(8).toInt();				// y
			file->readLine();												// End: 14BD
			file->readLine();												// Length: 50
			file->readLine();												// empty line
			if (file->atEnd())
				break;

			Level* newLevel = new Level(x, y);
			installCells(file, newLevel);

			mapLevels.insert(n, newLevel);
		}
	}
}

void Maps::installCells(QFile* file, Level* newLevel)
{
	char c;
	for (int j=0; j<newLevel->y; j++)
	{
		for (int i=0; i<newLevel->x; i++)
		{
			file->getChar(&c);
			if (c == ' ')
				newLevel->field[i][j] = empty;
			else if (c == 'X')
				newLevel->field[i][j] = wall;
			else if (c == '.')
				newLevel->field[i][j] = destination;
			else if (c == '*')
				newLevel->field[i][j] = box;
			else if (c == '@')
			{
				newLevel->field[i][j] = man;
				newLevel->man_x = i;
				newLevel->man_y = j;
			}
			else if (c == '&')
				newLevel->field[i][j] = destBox;
			else
				qDebug() << "ERROR: ______________________________________________________________ UNNOWN SYMBOL IN LEVEL";
		}
		file->getChar(&c);													// new line
	}
}
