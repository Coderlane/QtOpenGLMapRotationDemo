#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    mazeW = NULL;
    size = 10;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_launchButton_clicked()
{
    ui->launchButton->setEnabled(false);

    QMazeGen newMaze;
    newMaze.setSize(size);
    newMaze.makeMaze();

    mazeW = new MazeWindow();
    connect(mazeW, SIGNAL(emitClose()), this, SLOT(windowClosed()));
    mazeW->setMaze(size, newMaze.getMaze());
}

void MainWindow::on_mapSlider_valueChanged(int value)
{
    size = value;
    ui->mapLabel->setText("Map Size: " + QString::number(size) + " by " + QString::number(size));
}

void MainWindow::windowClosed()
{
    ui->launchButton->setEnabled(true);
    //delete mazeW;
    mazeW = NULL;
}

