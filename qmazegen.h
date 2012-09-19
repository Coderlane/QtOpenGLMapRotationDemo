#ifndef QMAZEGEN_H
#define QMAZEGEN_H

#include <QObject>
#include <QVector>

// Using code from Whyrusleeping https://github.com/whyrusleeping/MazeGenerator

class QMazeGen : public QObject
{
    Q_OBJECT
public:
    explicit QMazeGen(QObject *parent = 0);
    void setSize(int);
    QVector<QVector<short> > getMaze();

private:
    //Variables
    int size;
    QVector<QVector<short> >  m;

    //Functions
    bool isPassable(QVector<QVector<short> > &maze, int s, int cx, int cy);
    bool _nSideCheck(QVector<QVector<short> > &maze, int size, int x, int y, int n);
    bool threeSideCheck(QVector<QVector<short> > &maze, int size, int x, int y);
    bool deadSpaceCheck(QVector<QVector<short> > &maze, int size, int x, int y);

signals:
    void done();

public slots:
    void makeMaze();
    
};

#endif // QMAZEGEN_H
