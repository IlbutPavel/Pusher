#ifndef LEVELWIDGET_H
#define LEVELWIDGET_H

#include <QWidget>
#include <QGridLayout>

#include "level.h"
#include "controllevel.h"
#include "controllevelplay.h"
#include "controllevelhistory.h"
#include "observer.h"

class LevelWidget : public QWidget, public Observer
{
	Q_OBJECT
public:
	explicit LevelWidget(QWidget *parent = nullptr);
	explicit LevelWidget(Level* levelForCopy, ControlLevel* controlLevelForSet, QWidget *parent = nullptr);
	~LevelWidget() override;

	virtual void redrawPictureWidget(int i, int j, CellType type) override;
	virtual void finishPlay() override;

protected:
	virtual void mouseMoveEvent(QMouseEvent *event) override;
	virtual void mousePressEvent(QMouseEvent *event) override;


private:
	QGridLayout* layout;
	QVector<QVector<QWidget*>> matrixWidgets;
	Level* level;
	ControlLevel* controlLevel;



};

#endif // LEVELWIDGET_H
