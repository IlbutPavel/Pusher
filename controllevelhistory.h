#ifndef CONTROLLEVELHISTORY_H
#define CONTROLLEVELHISTORY_H

#include <QWidget>
#include <QShortcut>

#include "controllevel.h"

class ControlLevelHistory : public ControlLevel
{
	Q_OBJECT
public:
	ControlLevelHistory(QFile* file, Level* levelForSet, QWidget *parent = nullptr);


private slots:
	void keyLeftClicked();
	void keyRightClicked();

protected:
	virtual void setCellMoveCoordinate(int, int) override {}
	virtual void key_move(int dx, int dy) override;


private:
	QShortcut* keyLeft;
	QShortcut* keyRight;

	QList<HistoryAction*> history;
	QList<HistoryAction*>::iterator iteratorInHistory;

};

#endif // CONTROLLEVELHISTORY_H
