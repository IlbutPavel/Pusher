#include "controllevelhistory.h"

#include <QDebug>
#include <QMessageBox>


ControlLevelHistory::ControlLevelHistory(QFile* file, Level* levelForSet, QWidget *parent) : ControlLevel(levelForSet, parent)
{
	while (!file->atEnd())
	{
		QString line = file->readLine();
		QString type = line.section(';', 0, 0);
		if (type == MOVE)
		{
			int dx = line.section(';', 1, 1).toInt();
			int dy = line.section(';', 2, 2).toInt();
			bool moveBox = line.section(';', 3, 3).toInt();
			history.append(new HistoryAction(dx, dy, moveBox));
		}
		else if (type == TELE)
		{
			int xman = line.section(';', 1, 1).toInt();
			int yman = line.section(';', 2, 2).toInt();
			int xman_new = line.section(';', 3, 3).toInt();
			int yman_new = line.section(';', 4, 4).toInt();
			history.append(new HistoryAction(xman, yman, xman_new, yman_new));
		}
		else
			QMessageBox::warning(this, "Error", "History file error");
	}

	iteratorInHistory = history.begin();

	keyLeft = new QShortcut(this);
	keyLeft->setKey(Qt::Key_Left);
	connect(keyLeft, &QShortcut::activated, this, &ControlLevelHistory::keyLeftClicked);

	keyRight = new QShortcut(this);
	keyRight->setKey(Qt::Key_Right);
	connect(keyRight, &QShortcut::activated, this, &ControlLevelHistory::keyRightClicked);
}

void ControlLevelHistory::keyLeftClicked()
{
	if (iteratorInHistory != history.begin())
	{
		iteratorInHistory--;

		HistoryAction* action = *iteratorInHistory;
		if (action->type == moveAction)
			cancel_move(action->dx, action->dy, action->moveBox);
		else
			teleportManWithoutHistory(action->xfrom, action->yfrom);
	}
}

void ControlLevelHistory::keyRightClicked()
{
	if (iteratorInHistory != history.end())
	{
		HistoryAction* action = *iteratorInHistory;
		if (action->type == moveAction)
			key_move(action->dx, action->dy);
		else
			teleportManWithoutHistory(action->xdest, action->ydest);

		iteratorInHistory++;
	}
}

void ControlLevelHistory::key_move(int dx, int dy)
{
	int man_x_new = level->man_x + dx;
	int man_y_new = level->man_y + dy;
	int box_x_new = level->man_x + dx*2;
	int box_y_new = level->man_y + dy*2;
	const CellType man_cell_new = level->getFieldCell(man_x_new, man_y_new);
	const CellType box_cell_new = level->getFieldCell(box_x_new, box_y_new);

	if ((man_cell_new == box || man_cell_new == destBox) && (box_cell_new == empty || box_cell_new == destination))
	{
		if (box_cell_new == empty)
			level->setFieldCell(box_x_new, box_y_new, box);
		else
			level->setFieldCell(box_x_new, box_y_new, destBox);
	}

	teleportManWithoutHistory(man_x_new, man_y_new);
}
