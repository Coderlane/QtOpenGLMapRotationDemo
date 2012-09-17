#include "mazewindow.h"
#include "ui_mazewindow.h"

MazeWindow::MazeWindow(QWidget *parent, int s) : QWidget(parent), ui(new Ui::MazeWindow)
{
    ui->setupUi(this);
    size = s;
    setCursor(Qt::OpenHandCursor);
    showFullScreen();
}
MazeWindow::~MazeWindow()
{
    delete ui;
}

void MazeWindow::setMaze(int s, QVector<QVector<short> > nM)
{
    size = s;
    ui->glWidget->setupSim(s, nM);
}
void MazeWindow::keyPressEvent(QKeyEvent *pEvent)
{
    if(pEvent->key() == Qt::Key_Escape)
    {
        setCursor(Qt::ArrowCursor); // Unhide the cursor
        // Pause the game when ESC is pressed
        ui->glWidget->pause();
        if(QMessageBox::question(this, "Exit", "Would you like to exit", QMessageBox::Yes, QMessageBox::No) == QMessageBox::Yes)
        {
            // Exit
            // emit closeGameWindow();
            emit emitClose();
            this->close(); //Probably not necessary, but I'm pretty sure everything will be gone.
        }
        // Back to the action!
        ui->glWidget->unpause();
        setCursor(Qt::OpenHandCursor); // Back to hiding
    }
    else
        QWidget::keyPressEvent(pEvent);
}
