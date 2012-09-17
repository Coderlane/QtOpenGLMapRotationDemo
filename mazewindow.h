#ifndef MAZEWINDOW_H
#define MAZEWINDOW_H

#include <QWidget>
#include <QMessageBox>
#include <QKeyEvent>
#include <QVector>

namespace Ui {
class MazeWindow;
}

class MazeWindow : public QWidget
{
    Q_OBJECT
    
public:
    explicit MazeWindow(QWidget *parent = 0, int size = 10);
    ~MazeWindow();
    void setMaze(int size, QVector<QVector<short> > nM);
    
protected:
    void keyPressEvent( QKeyEvent* pEvent );

private:
    Ui::MazeWindow *ui;
    int size;

signals:
    void emitClose();

};

#endif // MAZEWINDOW_H
