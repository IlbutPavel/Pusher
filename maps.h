#ifndef MAPS_H
#define MAPS_H

#include <QObject>
#include <QMap>
#include <QFile>

#include "level.h"

class Maps : public QObject
{
	Q_OBJECT
public:
	explicit Maps(QObject *parent = nullptr);

	QMap<int, Level*> mapLevels;

signals:

private:
	void installCells(QFile* file, Level* newLevel);

};

#endif // MAPS_H
