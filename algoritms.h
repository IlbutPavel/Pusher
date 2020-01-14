#ifndef ALGORITMS_H
#define ALGORITMS_H

#include <QObject>
#include <QSet>

#include "level.h"

class Algoritms : public QObject
{
	Q_OBJECT
public:
	explicit Algoritms(QObject *parent = nullptr);


	struct moveCell
	{
		int dist;
		bool closed;
	};

	static bool moveManForMouse(int xdest, int ydest, Level* level);



signals:



private:

	static void backTrace();




};

#endif // ALGORITMS_H
