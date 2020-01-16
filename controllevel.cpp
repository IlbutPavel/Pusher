#include "controllevel.h"
#include <QShortcut>
#include <QMouseEvent>
#include <QDebug>
#include <QMessageBox>


ControlLevel::ControlLevel(Level* levelForSet, QWidget *parent) : QWidget(parent)
{
	level = levelForSet;
	maker = new Algoritms(level);

	QShortcut* keyUp = new QShortcut(this);
	keyUp->setKey(Qt::Key_Up);
	connect(keyUp, &QShortcut::activated, this, &ControlLevel::keyUpClicked);

	QShortcut* keyDown = new QShortcut(this);
	keyDown->setKey(Qt::Key_Down);
	connect(keyDown, &QShortcut::activated, this, &ControlLevel::keyDownClicked);

	QShortcut* keyLeft = new QShortcut(this);
	keyLeft->setKey(Qt::Key_Left);
	connect(keyLeft, &QShortcut::activated, this, &ControlLevel::keyLeftClicked);

	QShortcut* keyRight = new QShortcut(this);
	keyRight->setKey(Qt::Key_Right);
	connect(keyRight, &QShortcut::activated, this, &ControlLevel::keyRightClicked);

	QShortcut* keyCancel = new QShortcut(this);
	keyCancel->setKey(Qt::CTRL + Qt::Key_Z);
	connect(keyCancel, &QShortcut::activated, this, &ControlLevel::keyCancelClicked);
}

ControlLevel::~ControlLevel()
{
	delete maker;
}

void ControlLevel::key_move(int dx, int dy)
{
	int man_x_new = level->man_x + dx;
	int man_y_new = level->man_y + dy;
	int box_x_new = level->man_x + dx*2;
	int box_y_new = level->man_y + dy*2;
	bool moveMan = false;
	bool moveBox = false;
	CellType* man_cell_new = &(level->field[man_x_new][man_y_new]);
	CellType* box_cell_new = &(level->field[box_x_new][box_y_new]);

	if (*man_cell_new == empty || *man_cell_new == destination)
	{
		moveMan = true;
	}
	else if ((*man_cell_new == box || *man_cell_new == destBox) && (*box_cell_new == empty || *box_cell_new == destination))
	{
		if (*box_cell_new == empty)
			*box_cell_new = box;
		else
			*box_cell_new = destBox;
		emit needRedrawPictureWidget(box_x_new, box_y_new, *box_cell_new);

		moveMan = true;
		moveBox = true;
	}

	if (moveMan)
	{
		teleportManWithoutHistory(man_x_new, man_y_new);
		history.push(new HistoryAction(dx, dy, moveBox));
	}
	if (maker->isCongratulation())
		QMessageBox::information(this, "Congratulation", "Level is complite!!!");
}

void ControlLevel::cancel_move(int dx, int dy, bool moveBox)
{
	int man_x_old = level->man_x - dx;
	int man_y_old = level->man_y - dy;
	int box_x_old = level->man_x;
	int box_y_old = level->man_y;

	int box_x = level->man_x + dx;
	int box_y = level->man_y + dy;
	CellType* box_cell = &(level->field[box_x][box_y]);
	CellType* box_cell_old = &(level->field[box_x_old][box_y_old]);

	teleportManWithoutHistory(man_x_old, man_y_old);

	if (moveBox)
	{
		if (*box_cell == box)
			*box_cell = empty;
		else
			*box_cell = destination;
		emit needRedrawPictureWidget(box_x, box_y, *box_cell);

		if (*box_cell_old == empty)
			*box_cell_old = box;
		else
			*box_cell_old = destBox;
		emit needRedrawPictureWidget(box_x_old, box_y_old, *box_cell_old);
	}
}

void ControlLevel::teleportMan(int man_x_new, int man_y_new)
{
	if (man_x_new != level->man_x || man_y_new != level->man_y)
	{
		history.push(new HistoryAction(level->man_x, level->man_y));
		teleportManWithoutHistory(man_x_new, man_y_new);
	}
}

void ControlLevel::teleportManWithoutHistory(int man_x_new, int man_y_new)
{
	CellType* man_cell = &(level->field[level->man_x][level->man_y]);
	CellType* man_cell_new = &(level->field[man_x_new][man_y_new]);
	if (*man_cell == man)
		*man_cell = empty;
	else
		*man_cell = destination;
	emit needRedrawPictureWidget(level->man_x, level->man_y, *man_cell);

	if (*man_cell_new == empty || *man_cell_new == box)
		*man_cell_new = man;
	else
		*man_cell_new = destMan;
	emit needRedrawPictureWidget(man_x_new, man_y_new, *man_cell_new);

	level->man_x = man_x_new;
	level->man_y = man_y_new;
}

void ControlLevel::setCellMoveCoordinate(int i, int j)
{
	if (i == pressMouse_i && j == pressMouse_j)
		return;
	if (i >= level->x || j >= level->y)
		return;

	if (level->field[pressMouse_i][pressMouse_j] == box || level->field[pressMouse_i][pressMouse_j] == destBox)
	{
		if (j == pressMouse_j-1)
		{
			if (maker->moveManForMouse(i, pressMouse_j+1, level))
			{
				teleportMan(i, pressMouse_j+1);
				keyUpClicked();
			}
			pressMouse_j = j;
		}
		if (j == pressMouse_j+1)
		{
			if (maker->moveManForMouse(i, pressMouse_j-1, level))
			{
				teleportMan(i, pressMouse_j-1);
				keyDownClicked();
			}
			pressMouse_j = j;
		}
		if (i == pressMouse_i-1)
		{
			if (maker->moveManForMouse(pressMouse_i+1, j, level))
			{
				teleportMan(pressMouse_i+1, j);
				keyLeftClicked();
			}
			pressMouse_i = i;
		}
		if (i == pressMouse_i+1)
		{
			if (maker->moveManForMouse(pressMouse_i-1, j, level))
			{
				teleportMan(pressMouse_i-1, j);
				keyRightClicked();
			}
			pressMouse_i = i;
		}
	}
}

void ControlLevel::setCellPressCoordinate(int i, int j)
{
	pressMouse_i = i;
	pressMouse_j = j;
}


void ControlLevel::keyUpClicked()
{
	key_move(0, -1);
}

void ControlLevel::keyDownClicked()
{
	key_move(0, 1);
}

void ControlLevel::keyLeftClicked()
{
	key_move(-1, 0);
}

void ControlLevel::keyRightClicked()
{
	key_move(1, 0);
}

void ControlLevel::keyCancelClicked()
{
	if (!history.empty())
	{
		HistoryAction* lastAction = history.pop();
		if (lastAction->type == moveAction)
			cancel_move(lastAction->dx, lastAction->dy, lastAction->moveBox);
		else
			teleportManWithoutHistory(lastAction->xfrom, lastAction->yfrom);

		delete lastAction;
	}
}







