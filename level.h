#ifndef LEVEL_H
#define LEVEL_H

#include <QObject>
#include <QVector>

enum CellType {
	empty = 0,
	wall,
	destination,
	box,
	man,
	destBox,
	destMan
};

class Level : public QObject
{
	Q_OBJECT
public:
	explicit Level(int xx, int yy, QObject *parent = nullptr);
	explicit Level(Level* needCopy, QObject *parent = nullptr);

	int x;
	int y;

	int man_x;
	int man_y;

	QVector<QVector<CellType>> field;

signals:

};

#endif // LEVEL_H
