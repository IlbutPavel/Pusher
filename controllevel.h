#ifndef CONTROLLEVEL_H
#define CONTROLLEVEL_H

#include <QWidget>
#include <QStack>

#include "level.h"
#include "historyaction.h"
#include "algoritms.h"

class ControlLevel : public QWidget
{
	Q_OBJECT
public:
	explicit ControlLevel(Level* levelForSet, QWidget *parent = nullptr);

	void setCellMoveCoordinate(int i, int j);
	void setCellPressCoordinate(int i, int j);


signals:
	void needRedrawPictureWidget(int i, int j, CellType type);


private slots:
	void keyUpClicked();
	void keyDownClicked();
	void keyLeftClicked();
	void keyRightClicked();
	void keyCancelClicked();

private:

	Level* level;
	QStack<HistoryAction*> history;

	Algoritms* maker;

	int pressMouse_i;
	int pressMouse_j;

	void key_move(int dx, int dy);
	void cancel_move(int dx, int dy, bool moveBox);
	void teleportMan(int man_x_new, int man_y_new);
	void teleportManWithoutHistory(int man_x_new, int man_y_new);
};

#endif // CONTROLLEVEL_H
