#ifndef ALGORITMS_H
#define ALGORITMS_H

#include <QObject>
#include <QSet>
#include <QVector>
#include <QList>

#include "level.h"

class Algoritms : public QObject
{
	Q_OBJECT
public:
	explicit Algoritms(Level* level, QObject *parent = nullptr);
	~Algoritms();

	bool moveManForMouse(int xdest, int ydest, Level* level);
	bool isCongratulation();

private:

	static void backTrace();
	Level* level;

	struct MoveCell
	{
		int dist;
		bool isClosed;
	};
	QVector<QVector<MoveCell>> moveField;

};

#endif // ALGORITMS_H
