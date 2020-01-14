#ifndef LEVEL_H
#define LEVEL_H

#include <QObject>


enum CellType {
	empty = 0,
	wall,
	destination,
	box,
	man,
	destBox,
	destMan
};



class Level : public QObject
{
	Q_OBJECT
public:
	explicit Level(int xx, int yy, QObject *parent = nullptr);
	explicit Level(Level* needCopy);


	int x;
	int y;

	int man_x;
	int man_y;

	CellType** field;



signals:

};

#endif // LEVEL_H