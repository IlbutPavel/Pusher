#ifndef OBSERVER_H
#define OBSERVER_H

//#include "level.h"

enum CellType {
	empty = 0,
	wall = 8,
	destination = 1,
	box = 2,
	man = 5,
	destBox = 3,
	destMan = 6
};

class Observer
{
public:
	Observer();
	virtual ~Observer();

	virtual void redrawPictureWidget(int i, int j, CellType type) = 0;
	virtual void finishPlay() = 0;
};

#endif // OBSERVER_H
