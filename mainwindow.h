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


private slots:
	void spinBoxChangeLevel(int key);
	void changeLevel(Level* level, ControlLevel* controlLevel);
	void compressWindow();

	void startButtonClicked();
	void stopButtonClicked();
	void loadButtonClicked();


private:
	QVBoxLayout* layout;
	LevelWidget* levelWidget;

	QSpinBox* choiseLevel;
	QPushButton* startButton;
	QPushButton* stopButton;
	QPushButton* loadButton;

	Maps* maps;
	QTimer* timerResize;

};
#endif // MAINWINDOW_H
