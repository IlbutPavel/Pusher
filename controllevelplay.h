#ifndef CONTROLLEVELPLAY_H
#define CONTROLLEVELPLAY_H

#include <QWidget>
#include <QShortcut>

#include "controllevel.h"


class ControlLevelPlay : public ControlLevel
{
	Q_OBJECT
public:
	ControlLevelPlay(Level* levelForSet, QWidget *parent = nullptr);
	~ControlLevelPlay() override;

	virtual void setCellMoveCoordinate(int i, int j) override;

private slots:
	void keyUpClicked();
	void keyDownClicked();
	void keyLeftClicked();
	void keyRightClicked();
	void keyCancelClicked();


protected:
	virtual void key_move(int dx, int dy) override;

private:
	QShortcut* keyUp;
	QShortcut* keyDown;
	QShortcut* keyLeft;
	QShortcut* keyRight;
	QShortcut* keyCancel;


	QList<HistoryAction*> history;

	void teleportMan(int man_x_new, int man_y_new);

	void finishLevel();


	Algoritms* maker;
};

#endif // CONTROLLEVELPLAY_H
