#include "levelwidget.h"

#include "helperpictureswidget.h"
#include <QMouseEvent>
#include <QDebug>
#include <QShortcut>

#include "algoritms.h"

LevelWidget::LevelWidget(Level* levelForSet, QWidget *parent) : QWidget(parent)
{
	layout = new QGridLayout;
	layout->setContentsMargins(0, 0, 0, 0);
	layout->setSpacing(0);
	setLayout(layout);
	level = new Level(levelForSet);
	matrixWidgets = new QWidget**[level->x];
	for (int i=0; i<level->x; i++)
		matrixWidgets[i] = new QWidget*[level->y];




	for (int i=0; i<level->x; i++)
	{
		for (int j=0; j<level->y; j++)
		{
			matrixWidgets[i][j] = new QWidget;
			matrixWidgets[i][j]->setStyleSheet(HelperPicturesWidget::getStyleSheet(level->field[i][j]));
			layout->addWidget(matrixWidgets[i][j], j, i);
		}
	}

	resize(level->x * 30, level->y * 30);
	setMinimumSize(level->x * 30, level->y * 30);
	setMaximumSize(level->x * 30, level->y * 30);


	QShortcut* keyUp = new QShortcut(this);
	keyUp->setKey(Qt::Key_Up);
	connect(keyUp, &QShortcut::activated, this, &LevelWidget::keyUpClicked);

	QShortcut* keyDown = new QShortcut(this);
	keyDown->setKey(Qt::Key_Down);
	connect(keyDown, &QShortcut::activated, this, &LevelWidget::keyDownClicked);

	QShortcut* keyLeft = new QShortcut(this);
	keyLeft->setKey(Qt::Key_Left);
	connect(keyLeft, &QShortcut::activated, this, &LevelWidget::keyLeftClicked);

	QShortcut* keyRight = new QShortcut(this);
	keyRight->setKey(Qt::Key_Right);
	connect(keyRight, &QShortcut::activated, this, &LevelWidget::keyRightClicked);
}

void LevelWidget::keyUpClicked()
{
	key_move(level->man_x, level->man_y - 1, level->man_x, level->man_y - 2);
}

void LevelWidget::keyDownClicked()
{
	key_move(level->man_x, level->man_y + 1, level->man_x, level->man_y + 2);
}

void LevelWidget::keyLeftClicked()
{
	key_move(level->man_x - 1, level->man_y, level->man_x - 2, level->man_y);
}

void LevelWidget::keyRightClicked()
{
	key_move(level->man_x + 1, level->man_y, level->man_x + 2, level->man_y);
}


void LevelWidget::mouseMoveEvent(QMouseEvent* event)
{
	int i = event->x() / 30;
	int j = event->y() / 30;
//	qDebug() << i << j;
	if (i == drag_i && j == drag_j)
		return;
	if (i >= level->x || j >= level->y)
		return;

	if (level->field[drag_i][drag_j] == box || level->field[drag_i][drag_j] == destBox)
	{
		// up
		if (j == drag_j-1)
		{
			if (Algoritms::moveManForMouse(i, drag_j+1, level))
			{
				if (level->field[level->man_x][level->man_y] == man)
					level->field[level->man_x][level->man_y] = empty;
				else
					level->field[level->man_x][level->man_y] = destination;

				matrixWidgets[level->man_x][level->man_y]->setStyleSheet(HelperPicturesWidget::getStyleSheet(level->field[level->man_x][level->man_y]));

				if (level->field[i][drag_j+1] == empty)
					level->field[i][drag_j+1] = man;
				else
					level->field[i][drag_j+1] = destMan;

				matrixWidgets[i][drag_j+1]->setStyleSheet(HelperPicturesWidget::getStyleSheet(level->field[i][drag_j+1]));

				level->man_x = i;
				level->man_y = drag_j+1;

				keyUpClicked();
			}
			drag_j = j;
		}

		// down
		if (j == drag_j+1)
		{
			keyDownClicked();
			drag_j = j;
		}

		// left
		if (i == drag_i-1)
		{
			keyLeftClicked();
			drag_i = i;
		}

		// right
		if (i == drag_i+1)
		{
			keyRightClicked();
			drag_i = i;
		}
	}
}

void LevelWidget::mousePressEvent(QMouseEvent* event)
{
	drag_i = event->x() / 30;
	drag_j = event->y() / 30;
	qDebug() << "mousePressEvent" << drag_i << drag_j;
}

void LevelWidget::mouseReleaseEvent(QMouseEvent* event)
{
	Q_UNUSED(event)
}

void LevelWidget::key_move(int mv_x, int mv_y, int mv_xx, int mv_yy)
{
	bool moveMan = false;
	CellType* mn = &(level->field[level->man_x][level->man_y]);
	CellType* mv = &(level->field[mv_x][mv_y]);
	CellType* mvv = &(level->field[mv_xx][mv_yy]);

	if (*mv == empty || *mv == destination)
	{
		moveMan = true;
	}
	else if ((*mv == box || *mv == destBox) && (*mvv == empty || *mvv == destination))
	{
		if (*mvv == empty)
			*mvv = box;
		else
			*mvv = destBox;
		matrixWidgets[mv_xx][mv_yy]->setStyleSheet(HelperPicturesWidget::getStyleSheet(*mvv));

		moveMan = true;
	}

	if (moveMan)
	{
		if (*mn == man)
			*mn = empty;
		else
			*mn = destination;
		matrixWidgets[level->man_x][level->man_y]->setStyleSheet(HelperPicturesWidget::getStyleSheet(*mn));

		if (*mv == empty || *mv == box)
			*mv = man;
		else
			*mv = destMan;
		matrixWidgets[mv_x][mv_y]->setStyleSheet(HelperPicturesWidget::getStyleSheet(*mv));

		level->man_x = mv_x;
		level->man_y = mv_y;
	}
}






