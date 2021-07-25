#ifndef HISTORYACTION_H
#define HISTORYACTION_H

enum HistoryType {
	moveAction,
	teleportationAction
};

class HistoryAction
{
public:
	explicit HistoryAction(int init_dx, int init_dy, bool init_moveBox);
	explicit HistoryAction(int init_xfrom, int init_yfrom, int init_xdest, int init_dest);

	HistoryType type;

	int dx;
	int dy;
	bool moveBox;

	int xfrom;
	int yfrom;
	int xdest;
	int ydest;
};

#endif // HISTORYACTION_H
