#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QGLWidget>
#include <GL/glu.h>
//#include <GL/freeglut.h>
#include <QTimer>
#include <QMouseEvent>
#include <QList>
#include <QVector>

struct Coord
{
    float x;
    float y;
    float z;
};

struct Grid
{
    int x;
    int y;
};

const GLfloat LightAmbient[]= { 0.5f, 0.5f, 0.5f, 0.0f };
const GLfloat LightDiffuse[]= { 10.0f, 10.0f, 10.0f, 1.0f };
const GLfloat LightPosition[]= {0.0f, 0.0f, 10.0f, 10.0f };

const GLfloat reflectance[4] = { 0.0f, 0.8f, 0.0f, 1.0f };
const GLfloat reflectance1[4] = { 0.5f, 0.1f, 0.0f, 1.0f };
const GLfloat reflectance2[4] = { 1.0f, 0.0f, 0.0f, 1.0f };


// Ball Object
const int    ball_sides   = 30;
const int    ball_sectors = 30;
const double ball_size    = .666;
// Ball Movement
const double ball_dy_max  = .1;
const double ball_dx_max  = .1;
const double ball_ds      = 1;

class GLWidget : public QGLWidget
{
    Q_OBJECT
public:
    explicit GLWidget(QWidget *parent = 0);

    void ballUp();
    void ballDown();
    void ballLeft();
    void ballRight();

    void ballUpRel();
    void ballDownRel();
    void ballLeftRel();
    void ballRightRel();
protected:
    void initializeGL();
    void paintGL();
    void resizeGL(int width, int height);

    void mousePressEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *event);

    void setXRotation(int angle);
    void setYRotation(int angle);
    void setZRotation(int angle);
    void normalizeAngle(int *angle);

private:
    // Variables
    QPoint lastPos;
    GLuint maze;
    GLuint wall;
    GLuint ball;

    int sides;
    int xRot;
    int yRot;
    int zRot;
    QTimer *timer;
    QList<Coord> wallList;
    QVector<QVector<short> > m;

    float ballDY;
    float ballDX;
    float ballRadius;
    Coord ballPos;

    // Functions
    // Ball
    GLuint newBall();
    bool checkX(Coord c);
    bool checkY(Coord c);
    bool checkAround(Coord ball, float radius);
    // Maze
    GLuint newMaze();
    // Wall
    GLuint newWall();
    void drawWalls();
    // Generic
    void drawList(GLuint p, double dx, double dy, double dz);


    // Hit testing
    Coord toCoord2D(Grid g);
    Grid toGrid2D(Coord c);
    QVector<Grid> checkOpenAround(Grid g);

signals:
    
public slots:
    void loop();
    void pause();
    void unpause();
    void setupSim(int sides, QVector<QVector<short> > nM);  
};

#endif // GLWIDGET_H
