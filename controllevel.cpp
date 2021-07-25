#include "controllevel.h"
#include <QMouseEvent>
#include <QDebug>

ControlLevel::ControlLevel(Level* levelForSet, QWidget *parent) : QWidget(parent)
{
	level = levelForSet;
}

ControlLevel::~ControlLevel()
{

}

void ControlLevel::teleportManWithoutHistory(int man_x_new, int man_y_new)
{
	const CellType man_cell = level->getFieldCell(level->man_x, level->man_y);
	const CellType man_cell_new = level->getFieldCell(man_x_new, man_y_new);
	if (man_cell == man)
		level->setFieldCell(level->man_x, level->man_y, empty);
	else
		level->setFieldCell(level->man_x, level->man_y, destination);

	if (man_cell_new == empty || man_cell_new == box)
		level->setFieldCell(man_x_new, man_y_new, man);
	else
		level->setFieldCell(man_x_new, man_y_new, destMan);

	level->man_x = man_x_new;
	level->man_y = man_y_new;
}

void ControlLevel::setCellPressCoordinate(int i, int j)
{
	pressMouse_i = i;
	pressMouse_j = j;
}

void ControlLevel::cancel_move(int dx, int dy, bool moveBox)
{
	int man_x_old = level->man_x - dx;
	int man_y_old = level->man_y - dy;
	int box_x_old = level->man_x;
	int box_y_old = level->man_y;

	int box_x = level->man_x + dx;
	int box_y = level->man_y + dy;

	teleportManWithoutHistory(man_x_old, man_y_old);

	if (moveBox)
	{
		if (level->getFieldCell(box_x, box_y) == box)
			level->setFieldCell(box_x, box_y, empty);
		else
			level->setFieldCell(box_x, box_y, destination);

		if (level->getFieldCell(box_x_old, box_y_old) == empty)
			level->setFieldCell(box_x_old, box_y_old, box);
		else
			level->setFieldCell(box_x_old, box_y_old, destBox);
	}
}





