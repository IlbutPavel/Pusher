#include "mainwindow.h"

#include "helperpictureswidget.h"

#include <QVBoxLayout>
#include <QTimer>
#include <QDebug>


MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
{
	timerResize = new QTimer;
	timerResize->setSingleShot(true);
	connect(timerResize, &QTimer::timeout, this, &MainWindow::compressWindow);

	QWidget* centralWidget = new QWidget;
	layout = new QVBoxLayout;
	choiseLevel = new QSpinBox;
	connect(choiseLevel, static_cast<void(QSpinBox::*)(int)>(&QSpinBox::valueChanged), this, &MainWindow::changeLevel);
	startButton = new QPushButton;
	stopButton = new QPushButton;
	startButton->setText("Start");
	stopButton->setText("Stop");
	connect(startButton, &QPushButton::clicked, this, &MainWindow::startButtonClicked);
	connect(stopButton, &QPushButton::clicked, this, &MainWindow::stopButtonClicked);
	stopButton->setEnabled(false);
	QHBoxLayout* controlLayout = new QHBoxLayout;


	maps = new Maps(this);											//create arhive with maps
	levelWidget = new LevelWidget(maps->mapLevels.value(44));

	setCentralWidget(centralWidget);
	centralWidget->setLayout(layout);
	controlLayout->addWidget(choiseLevel);
	controlLayout->addWidget(startButton);
	controlLayout->addWidget(stopButton);
	controlLayout->addStretch();
	layout->addLayout(controlLayout);
	layout->addStretch();
	layout->addWidget(levelWidget);

	choiseLevel->setAlignment(Qt::AlignLeft);
	choiseLevel->setMinimum(1);
	choiseLevel->setMaximum(maps->mapLevels.size());
	choiseLevel->show();
}

MainWindow::~MainWindow()
{
}

void MainWindow::changeLevel(int key)
{
	layout->removeWidget(levelWidget);
	delete levelWidget;
	levelWidget = new LevelWidget(maps->mapLevels.value(key));
	layout->addWidget(levelWidget);
	levelWidget->setEnabled(false);

	timerResize->start(20);
}

void MainWindow::compressWindow()
{
	resize(1, 1);
}

void MainWindow::startButtonClicked()
{
	choiseLevel->setEnabled(false);
	startButton->setEnabled(false);
	stopButton->setEnabled(true);
	levelWidget->setEnabled(true);
}

void MainWindow::stopButtonClicked()
{
	choiseLevel->setEnabled(true);
	startButton->setEnabled(true);
	stopButton->setEnabled(false);
	levelWidget->setEnabled(false);
}

