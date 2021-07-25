#ifndef LEVEL_H
#define LEVEL_H

#include <QObject>
#include <QVector>
#include <QList>

#include "observer.h"

//enum CellType {
//	empty = 0,
//	wall,
//	destination,
//	box,
//	man,
//	destBox,
//	destMan
//};

class Level : public QObject
{
	Q_OBJECT
public:
	explicit Level(int nn, int xx, int yy, QObject *parent = nullptr);
	explicit Level(Level* needCopy, QObject *parent = nullptr);
	QList<Observer*> observers;

	int n;
	int x;
	int y;

	int man_x;
	int man_y;


	CellType getFieldCell(int i, int j);
	void setFieldCell(int i, int j, CellType cell);

	void addObserver(Observer* observer);

	void setFinishPlay();

private:
	QVector<QVector<CellType>> field;

signals:

};

#endif // LEVEL_H
