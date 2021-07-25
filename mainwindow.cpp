#include "mainwindow.h"

#include "helperpictureswidget.h"

#include <QVBoxLayout>
#include <QTimer>
#include <QDebug>
#include <QFileDialog>


MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
{
	timerResize = new QTimer(this);
	timerResize->setSingleShot(true);
	connect(timerResize, &QTimer::timeout, this, &MainWindow::compressWindow);

	QWidget* centralWidget = new QWidget;
	layout = new QVBoxLayout;
	choiseLevel = new QSpinBox;
	connect(choiseLevel, static_cast<void(QSpinBox::*)(int)>(&QSpinBox::valueChanged), this, &MainWindow::spinBoxChangeLevel);
	startButton = new QPushButton;
	stopButton = new QPushButton;
	loadButton = new QPushButton;
	startButton->setText("Start");
	stopButton->setText("Stop");
	loadButton->setText("LoadSolve");
	connect(startButton, &QPushButton::clicked, this, &MainWindow::startButtonClicked);
	connect(stopButton, &QPushButton::clicked, this, &MainWindow::stopButtonClicked);
	connect(loadButton, &QPushButton::clicked, this, &MainWindow::loadButtonClicked);
	stopButton->setEnabled(false);
	QHBoxLayout* controlLayout = new QHBoxLayout;


	maps = new Maps(this);											//create arhive with maps
	levelWidget = new LevelWidget();

	setCentralWidget(centralWidget);
	centralWidget->setLayout(layout);
	controlLayout->addWidget(choiseLevel);
	controlLayout->addWidget(startButton);
	controlLayout->addWidget(stopButton);
	controlLayout->addWidget(loadButton);
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

void MainWindow::spinBoxChangeLevel(int key)
{
	Level* level = new Level(maps->mapLevels.value(key));
	ControlLevelPlay* controlLevel = new ControlLevelPlay(level);
	changeLevel(level, controlLevel);
}

void MainWindow::changeLevel(Level* level, ControlLevel* controlLevel)
{
	layout->removeWidget(levelWidget);
	delete levelWidget;

	levelWidget = new LevelWidget(level, controlLevel);
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
	loadButton->setEnabled(false);
	stopButton->setEnabled(true);
	levelWidget->setEnabled(true);
}

void MainWindow::stopButtonClicked()
{
	choiseLevel->setEnabled(true);
	startButton->setEnabled(true);
	loadButton->setEnabled(true);
	stopButton->setEnabled(false);
	levelWidget->setEnabled(false);
}

void MainWindow::loadButtonClicked()
{
	QString fullFileName = QFileDialog::getOpenFileName(this, tr("Open a Movie"), "./");

	if (!fullFileName.isEmpty())
	{
		QFile* file = new QFile(fullFileName);
		if (!file->open(QIODevice::ReadOnly | QIODevice::Text))
		{
			qDebug() << "file " + fullFileName + " don't open";
		}
		else
		{
			int nLevel = file->readLine().trimmed().toInt();
			Level* level = new Level(maps->mapLevels.value(nLevel));
			ControlLevelHistory* controlLevel = new ControlLevelHistory(file, level);
			changeLevel(level, controlLevel);


			delete file;


			choiseLevel->setEnabled(false);
			startButton->setEnabled(false);
			loadButton->setEnabled(false);
			stopButton->setEnabled(true);
			levelWidget->setEnabled(true);
		}
	}
}








