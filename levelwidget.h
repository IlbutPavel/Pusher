#ifndef LEVELWIDGET_H
#define LEVELWIDGET_H

#include <QWidget>
#include <QGridLayout>

#include "level.h"
#include "controllevel.h"

class LevelWidget : public QWidget
{
	Q_OBJECT
public:
	explicit LevelWidget(Level* levelForCopy, QWidget *parent = nullptr);
	~LevelWidget() override;

signals:



private slots:
	void redrawPictureWidget(int i, int j, CellType type);

protected:
	virtual void mouseMoveEvent(QMouseEvent *event) override;
	virtual void mousePressEvent(QMouseEvent *event) override;


private:
	QGridLayout* layout;
	QWidget*** matrixWidgets;
	Level* level;
	ControlLevel* controlLevel;



};

#endif // LEVELWIDGET_H
