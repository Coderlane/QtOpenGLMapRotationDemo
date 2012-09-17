#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "mazewindow.h"
#include "qmazegen.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
private:
    Ui::MainWindow *ui;
    MazeWindow *mazeW;
    int size;

public slots:
    void windowClosed();

private slots:
    void on_launchButton_clicked();
    void on_mapSlider_valueChanged(int value);


};

#endif // MAINWINDOW_H
