#include "controllevelplay.h"

#include <QDebug>
#include <QDateTime>

ControlLevelPlay::ControlLevelPlay(Level* levelForSet, QWidget *parent) : ControlLevel(levelForSet, parent)
{

	maker = new Algoritms(levelForSet, this);

	keyUp = new QShortcut(this);
	keyUp->setKey(Qt::Key_Up);
	connect(keyUp, &QShortcut::activated, this, &ControlLevelPlay::keyUpClicked);

	keyDown = new QShortcut(this);
	keyDown->setKey(Qt::Key_Down);
	connect(keyDown, &QShortcut::activated, this, &ControlLevelPlay::keyDownClicked);

	keyLeft = new QShortcut(this);
	keyLeft->setKey(Qt::Key_Left);
	connect(keyLeft, &QShortcut::activated, this, &ControlLevelPlay::keyLeftClicked);

	keyRight = new QShortcut(this);
	keyRight->setKey(Qt::Key_Right);
	connect(keyRight, &QShortcut::activated, this, &ControlLevelPlay::keyRightClicked);

	keyCancel = new QShortcut(this);
	keyCancel->setKey(Qt::CTRL + Qt::Key_Z);
	connect(keyCancel, &QShortcut::activated, this, &ControlLevelPlay::keyCancelClicked);
}

ControlLevelPlay::~ControlLevelPlay()
{
}

void ControlLevelPlay::setCellMoveCoordinate(int i, int j)
{
	if (i == pressMouse_i && j == pressMouse_j)
		return;
	if (i >= level->x || j >= level->y)
		return;

	if (level->getFieldCell(pressMouse_i, pressMouse_j) == box || level->getFieldCell(pressMouse_i, pressMouse_j) == destBox)
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


void ControlLevelPlay::keyUpClicked()
{
	key_move(0, -1);
}

void ControlLevelPlay::keyDownClicked()
{
	key_move(0, 1);
}

void ControlLevelPlay::keyLeftClicked()
{
	key_move(-1, 0);
}

void ControlLevelPlay::keyRightClicked()
{
	key_move(1, 0);
}

void ControlLevelPlay::keyCancelClicked()
{
	if (!history.empty())
	{
		HistoryAction* lastAction = history.back();
		history.pop_back();
		if (lastAction->type == moveAction)
			cancel_move(lastAction->dx, lastAction->dy, lastAction->moveBox);
		else
			teleportManWithoutHistory(lastAction->xfrom, lastAction->yfrom);

		delete lastAction;
	}
}

void ControlLevelPlay::key_move(int dx, int dy)
{
	int man_x_new = level->man_x + dx;
	int man_y_new = level->man_y + dy;
	int box_x_new = level->man_x + dx*2;
	int box_y_new = level->man_y + dy*2;
	if (box_x_new < 0 || box_x_new >= level->x || box_y_new < 0 || box_y_new >= level->y)
		return;
	bool moveMan = false;
	bool moveBox = false;
	bool needCheckOnCongratulation = false;
	const CellType man_cell_new = level->getFieldCell(man_x_new, man_y_new);
	const CellType box_cell_new = level->getFieldCell(box_x_new, box_y_new);

	if (man_cell_new == empty || man_cell_new == destination)
	{
		moveMan = true;
	}
	else if ((man_cell_new == box || man_cell_new == destBox) && (box_cell_new == empty || box_cell_new == destination))
	{
		if (box_cell_new == empty)
			level->setFieldCell(box_x_new, box_y_new, box);
		else
		{
			level->setFieldCell(box_x_new, box_y_new, destBox);
			needCheckOnCongratulation = true;
		}

		moveMan = true;
		moveBox = true;
	}

	if (moveMan)
	{
		teleportManWithoutHistory(man_x_new, man_y_new);
		history.append(new HistoryAction(dx, dy, moveBox));
	}
	if (needCheckOnCongratulation)
		if (maker->isCongratulation())
			finishLevel();
}

void ControlLevelPlay::teleportMan(int man_x_new, int man_y_new)
{
	if (man_x_new != level->man_x || man_y_new != level->man_y)
	{
		history.append(new HistoryAction(level->man_x, level->man_y, man_x_new, man_y_new));
		teleportManWithoutHistory(man_x_new, man_y_new);
	}
}



void ControlLevelPlay::finishLevel()
{
	level->setFinishPlay();

	//need save history
	QFile* file = new QFile("Level_" + QString::number(level->n) + "___" + QDateTime::currentDateTime().toString("yyyy-MM-dd___hh-mm-ss").toUtf8() + ".txt", this);
	QString writeString;
	QString d = ";";
	if (!file->open(QIODevice::WriteOnly | QIODevice::Text))
	{
		qDebug() << "file **************history**************.txt don't created";
	}
	else
	{
		file->write((QString::number(level->n) + "\n").toStdString().c_str());
		while (!history.empty())
		{
			writeString = "";
			HistoryAction* action = history.front();
			history.pop_front();
			if (action->type == moveAction)
				writeString = MOVE + d + QString::number(action->dx) + d + QString::number(action->dy) + d + QString::number(action->moveBox) + d + "\n";
			else
				writeString = TELE + d + QString::number(action->xfrom) + d + QString::number(action->yfrom) + d + QString::number(action->xdest) + d + QString::number(action->ydest) + d + "\n";
			delete action;

			qDebug() << writeString;
			file->write(writeString.toStdString().c_str());
		}
		file->close();
	}
}
