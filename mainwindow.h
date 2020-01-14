#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QSpinBox>

#include "maps.h"
#include "levelwidget.h"


class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow(QWidget *parent = nullptr);
	~MainWindow();



	Maps* maps;



public slots:
	void changeLevel(int key);
	void compressWindow();

	void startButtonClicked();
	void stopButtonClicked();


private:
	QVBoxLayout* layout;
	LevelWidget* levelWidget;

	QSpinBox* choiseLevel;
	QPushButton* startButton;
	QPushButton* stopButton;

	QTimer* timerResize;

};
#endif // MAINWINDOW_H
