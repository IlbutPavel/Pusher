#include "levelwidget.h"

#include "helperpictureswidget.h"
#include <QMouseEvent>
#include <QDebug>
#include <QMessageBox>



LevelWidget::LevelWidget(QWidget* parent) : QWidget(parent)
{

}

LevelWidget::LevelWidget(Level* levelForCopy, ControlLevel* controlLevelForSet, QWidget *parent) : QWidget(parent)
{
	layout = new QGridLayout;
	layout->setContentsMargins(0, 0, 0, 0);
	layout->setSpacing(0);
	setLayout(layout);
	level = levelForCopy;
	level->setParent(this);
	level->addObserver(this);
	controlLevel = controlLevelForSet;
	controlLevel->setParent(this);

	matrixWidgets.resize(level->x);
	for (int i=0; i<level->x; i++)
		matrixWidgets[i].resize(level->y);

	for (int i=0; i<level->x; i++)
	{
		for (int j=0; j<level->y; j++)
		{
			matrixWidgets[i][j] = new QWidget;
			matrixWidgets[i][j]->setStyleSheet(HelperPicturesWidget::getStyleSheet(level->getFieldCell(i, j)));
			layout->addWidget(matrixWidgets[i][j], j, i);
		}
	}

	resize(level->x * SIZE_CELL, level->y * SIZE_CELL);
	setMinimumSize(level->x * SIZE_CELL, level->y * SIZE_CELL);
	setMaximumSize(level->x * SIZE_CELL, level->y * SIZE_CELL);
}

LevelWidget::~LevelWidget()
{
}

void LevelWidget::redrawPictureWidget(int i, int j, CellType type)
{
	matrixWidgets[i][j]->setStyleSheet(HelperPicturesWidget::getStyleSheet(type));
}

void LevelWidget::finishPlay()
{
	setEnabled(false);
	QMessageBox::information(this, "Congratulation", "Level is complite!!!");
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








