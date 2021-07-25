#ifndef CONTROLLEVEL_H
#define CONTROLLEVEL_H

#include <QWidget>
#include <QStack>
#include <QShortcut>

#include "level.h"
#include "historyaction.h"
#include "algoritms.h"

#define TELE "tele"
#define MOVE "move"


class ControlLevel : public QWidget
{
	Q_OBJECT
public:
	explicit ControlLevel(Level* levelForSet, QWidget *parent = nullptr);
	~ControlLevel();

	virtual void setCellMoveCoordinate(int i, int j) = 0;
	void setCellPressCoordinate(int i, int j);


protected:

	virtual void key_move(int dx, int dy) = 0;
	void teleportManWithoutHistory(int man_x_new, int man_y_new);

	Level* level;

	int pressMouse_i;
	int pressMouse_j;


	void cancel_move(int dx, int dy, bool moveBox);

};

#endif // CONTROLLEVEL_H
