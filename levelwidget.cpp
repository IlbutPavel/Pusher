#include "levelwidget.h"

#include "helperpictureswidget.h"
#include <QMouseEvent>
#include <QDebug>
#include <QCoreApplication>



LevelWidget::LevelWidget(Level* levelForCopy, QWidget *parent) : QWidget(parent)
{
	layout = new QGridLayout;
	layout->setContentsMargins(0, 0, 0, 0);
	layout->setSpacing(0);
	setLayout(layout);
	level = new Level(levelForCopy, this);					//недо конструктор копирования
	controlLevel = new ControlLevel(level, this);
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

	resize(level->x * SIZE_CELL, level->y * SIZE_CELL);
	setMinimumSize(level->x * SIZE_CELL, level->y * SIZE_CELL);
	setMaximumSize(level->x * SIZE_CELL, level->y * SIZE_CELL);

	connect(controlLevel, &ControlLevel::needRedrawPictureWidget, this, &LevelWidget::redrawPictureWidget);
}

LevelWidget::~LevelWidget()
{
	for (int i=0; i<level->x; i++)
		delete matrixWidgets[i];
	delete matrixWidgets;
}

void LevelWidget::redrawPictureWidget(int i, int j, CellType type)
{
	matrixWidgets[i][j]->setStyleSheet(HelperPicturesWidget::getStyleSheet(type));
}

void LevelWidget::mouseMoveEvent(QMouseEvent* event)
{
	int i = event->x() / SIZE_CELL;
	int j = event->y() / SIZE_CELL;
	controlLevel->setCellMoveCoordinate(i, j);
}

void LevelWidget::mousePressEvent(QMouseEvent* event)
{
	int i = event->x() / SIZE_CELL;
	int j = event->y() / SIZE_CELL;
	controlLevel->setCellPressCoordinate(i, j);
}








