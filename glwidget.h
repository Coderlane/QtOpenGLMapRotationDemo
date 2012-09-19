#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QGLWidget>
#include <GL/glu.h>
#include <QTimer>
#include <QMouseEvent>
#include <QList>
#include <QVector>

struct Wall
{
    double x;
    double y;
    double z;
};

const GLfloat LightAmbient[]= { 0.5f, 0.5f, 0.5f, 0.0f };
const GLfloat LightDiffuse[]= { 10.0f, 10.0f, 10.0f, 1.0f };
const GLfloat LightPosition[]= {0.0f, 0.0f, 10.0f, 10.0f };

const GLfloat reflectance[4] = { 0.0f, 0.8f, 0.0f, 1.0f };
const GLfloat reflectance1[4] = { 0.5f, 0.1f, 0.0f, 1.0f };
const GLfloat reflectance2[4] = { 1.0f, 0.0f, 0.0f, 1.0f };


class GLWidget : public QGLWidget
{
    Q_OBJECT
public:
    explicit GLWidget(QWidget *parent = 0);

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
    QTimer *timer;
    QPoint lastPos;
    GLuint maze;
    GLuint wall;

    int sides;
    int xRot;
    int yRot;
    int zRot;
    QList<Wall> wallList;

    // Functions
    // Maze
    GLuint newMaze();
    void drawMaze(GLuint p, double dx, double dy, double dz);
    // Wall
    GLuint newWall();
    void drawWalls();

    QVector<QVector<short> > m;

signals:
    
public slots:
    void loop();
    void pause();
    void unpause();
    void setupSim(int sides, QVector<QVector<short> > nM);  
};

#endif // GLWIDGET_H
