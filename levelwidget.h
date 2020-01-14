#ifndef LEVELWIDGET_H
#define LEVELWIDGET_H

#include <QWidget>
#include <QGridLayout>

#include "level.h"

class LevelWidget : public QWidget
{
	Q_OBJECT
public:
	explicit LevelWidget(Level* levelForSet, QWidget *parent = nullptr);


	Level* getlevel() const { return level; }

signals:




public slots:

	void keyUpClicked();
	void keyDownClicked();
	void keyLeftClicked();
	void keyRightClicked();


protected:
	virtual void mouseMoveEvent(QMouseEvent *event) override;
	virtual void mousePressEvent(QMouseEvent *event) override;
	virtual void mouseReleaseEvent(QMouseEvent *event) override;


private:
	QGridLayout* layout;
	QWidget*** matrixWidgets;
	Level* level;

	int drag_i;
	int drag_j;

	void key_move(int mv_x, int mv_y, int mv_xx, int mv_yy);

};

#endif // LEVELWIDGET_H
