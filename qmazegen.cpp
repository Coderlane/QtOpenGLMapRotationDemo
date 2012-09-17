#include "qmazegen.h"

#ifdef PRETTY
#define PVAL 2
#else
#define PVAL 3
#endif

QMazeGen::QMazeGen(QObject *parent) : QObject(parent)
{
    size = 0;
}

void QMazeGen::setSize(int s)
{
    size = s;
}

QVector<QVector<short> > QMazeGen::getMaze()
{
    return m;
}

void QMazeGen::makeMaze()
{
    m.resize(size);
    for(int i = 0; i < size; i++)
        m[i].resize(size);
    int tries = 0;

    while(tries < 60 * size * size)
    {
        int x = rand() % size;
        int y = rand() % size;

        if(!((x == 0 && y == 0) || (x == size - 1 && y == size - 1) || (m[x][y])))
        {
            m[x][y] = 1;

            if(!deadSpaceCheck(m,size,x,y) || threeSideCheck(m,size,x,y))
            {
                m[x][y] = 0;
                tries++;
                continue;
            }
            QVector<QVector<short> > cm(m);
            if(!isPassable(cm, size,0,0))
            {
                m[x][y] = 0;
                tries+=5;
            }
        }
    }
    emit done();
}

//returns false if placing a square in x,y creates dead space
bool QMazeGen::deadSpaceCheck(QVector<QVector<short> > &maze, int size, int x, int y)
{
    if(x > 0 && !maze[x-1][y])
    {
        QVector<QVector<short> > m(maze);
        if(!isPassable(m, size, x-1, y))
            return false;
    }
    if(x < size -1 && !maze[x+1][y])
    {
        QVector<QVector<short> > m(maze);
        if(!isPassable(m, size, x+1, y))
            return false;
    }

    if(y > 0 && !maze[x][y-1])
    {
        QVector<QVector<short> > m(maze);
        if(!isPassable(m, size, x, y-1))
            return false;
    }

    if(y < size -1 && !maze[x][y+1])
    {
        QVector<QVector<short> > m(maze);
        if(!isPassable(m, size, x, y+1))
            return false;
    }
    return true;
}

bool QMazeGen::threeSideCheck(QVector<QVector<short> > &maze, int size, int x, int y)
{
    bool ret = _nSideCheck(maze,size,x,y,2);

    if(!ret && x > 0)
        ret |= _nSideCheck(maze,size,x-1,y,PVAL);

    if(!ret && x < size-1)
        ret |= _nSideCheck(maze,size,x+1,y,PVAL);

    if(!ret && y>0)
        ret |= _nSideCheck(maze,size,x,y-1,PVAL);

    if(!ret && y < size-1)
        ret |= _nSideCheck(maze,size,x,y+1,PVAL);
    return ret;
}

bool QMazeGen::_nSideCheck(QVector<QVector<short> > &maze, int size, int x, int y, int n)
{
    int c = 0;
    if(x > 0)
    {
        if(maze[x-1][y])
            c++;
    }
    else
    {
        c++;
    }

    if(x < size - 1)
    {
        if(maze[x+1][y])
            c++;
    }
    else
    {
        c++;
    }

    if(y > 0)
    {
        if(maze[x][y-1])
            c++;
    }
    else
    {
        c++;
    }

    if(y < size - 1)
    {
        if(maze[x][y+1])
            c++;
    }
    else
    {
        c++;
    }

    return c > n;

}

bool QMazeGen::isPassable(QVector<QVector<short> > &maze, int s, int cx, int cy)
{
    if(cx < 0 || cy < 0 || cx >= s || cy >= s || maze[cx][cy]== 1 )
        return false;
    if(cx == s-1 && cy == s-1)
        return true;

    maze[cx][cy] = 1;
    if(isPassable(maze, s, cx + 1, cy))
    {
        return true;
    }

    if(isPassable(maze, s, cx, cy + 1))
    {
        return true;
    }
    if(isPassable(maze, s, cx - 1, cy))
    {
        return true;
    }

    if(isPassable(maze, s, cx, cy - 1))
    {
        return true;
    }
    return false;
}
