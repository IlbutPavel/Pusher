#include "historyaction.h"


HistoryAction::HistoryAction(int init_dx, int init_dy, bool init_moveBox)
{
	type = moveAction;
	dx = init_dx;
	dy = init_dy;
	moveBox = init_moveBox;
}

HistoryAction::HistoryAction(int init_xfrom, int init_yfrom)
{
	type = teleportationAction;
	xfrom = init_xfrom;
	yfrom = init_yfrom;
}


