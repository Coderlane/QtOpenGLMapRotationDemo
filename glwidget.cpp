#include "glwidget.h"

GLWidget::GLWidget(QWidget *parent) : QGLWidget(parent)
{
    sides = 0;
    timer = new QTimer(this);
    timer->setInterval(20);
    timer->stop();
    connect(timer, SIGNAL(timeout()), this, SLOT(loop()));
    xRot = 0;
    yRot = 0;
    zRot = 0;

}
void GLWidget::loop()
{
    updateGL();
}
void GLWidget::initializeGL()
{
    // Init Stuff
    glShadeModel(GL_SMOOTH);
    glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
    glClearDepth(1.0f);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_DEPTH_TEST);

    glLightfv(GL_LIGHT1, GL_AMBIENT,  LightAmbient);
    glLightfv(GL_LIGHT1, GL_DIFFUSE,  LightDiffuse);
    glLightfv(GL_LIGHT1, GL_POSITION, LightPosition);
}
void GLWidget::paintGL()
{
    qglClearColor(QColor(Qt::black));
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Show Text
    glColor3f(1.0f, 1.0f, 1.0f);
    renderText( 10,  9 , 0, "Map Demo", QFont("Ubuntu", 30, 10, false));  

    glPushMatrix();
    glRotated(xRot / 16.0, 1.0, 0.0, 0.0);
    glRotated(yRot / 16.0, 0.0, 1.0, 0.0);
    glRotated(zRot / 16.0, 0.0, 0.0, 1.0);
    drawMaze(maze, 0, 0, 0);
    drawWalls();
    glPopMatrix();
}
void GLWidget::resizeGL(int width, int height)
{
    // Safety Check! Wear your hard hat
    if(width == 0)
        width = 1;
    if(height == 0)
        height = 1;
    double ratio = (width>height?((double)width/(double)height):((double)height/(double)width));
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(30.0f,ratio,0.1f,100.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslated(0.0, 0.0, -40);
}
void GLWidget::pause()
{
    timer->stop();
}
void GLWidget::unpause()
{
    timer->start();
}
void GLWidget::setupSim(int s, QVector<QVector<short> > nM)
{
    m = nM;
    sides = s;
    wall = newWall();
    maze = newMaze();
    unpause();
    updateGL();

}
GLuint GLWidget::newMaze()
{
    GLuint list = glGenLists(1);
    glNewList(list, GL_COMPILE);
    glColor3f(0, 1, 0); // Green

    double space = (10.0/sides);

    // Outer Perimeter
    for(int i = 0; i <= sides; i ++)
    {
        glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, reflectance2);
        wallList.append((struct Wall) {  i*space, 10,space});
        wallList.append((struct Wall) {  i*space,-10,space});
        wallList.append((struct Wall) { -i*space, 10,space});
        wallList.append((struct Wall) { -i*space,-10,space});
        wallList.append((struct Wall) {-10,  i*space,space});
        wallList.append((struct Wall) { 10,  i*space,space});
        wallList.append((struct Wall) {-10, -i*space,space});
        wallList.append((struct Wall) { 10, -i*space,space});
    }
    // Actual Maze
    for(int a = 0; a < sides; a++)
    {
        for(int b = 0; b < sides; b++)
        {
            if(m[a][b] == 1)
            {
                wallList.append((struct Wall) {-10.0 + ((double)a*2*space),-10.0 + ((double)b*2*space), space});
            }
        }
    }

    // Rectangle
    glBegin(GL_LINE_LOOP);
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, reflectance1);
    glVertex3f(-10, -10, 0.0f);
    glVertex3f(-10, 10, 0.0f);
    glVertex3f(10, 10, 0.0f);
    glVertex3f(10, -10, 0.0f);
    glEnd();

    // Grid
    // Odd case, try to combine?
    if(sides%2 == 0)
    {
        double ratio = ((10.0/(double)sides))*2.0;
        glBegin(GL_LINES);
        glVertex3f(10, 0, 0.0f);
        glVertex3f(-10, 0, 0.0f);
        glEnd();
        for(int i = 0; i < sides/2.0; i++)
        {
            glBegin(GL_LINES);
            glVertex3f(10, i*ratio, 0.0f);
            glVertex3f(-10, i*ratio, 0.0f);
            glEnd();
            glBegin(GL_LINES);
            glVertex3f(10, -i*ratio, 0.0f);
            glVertex3f(-10, -i*ratio, 0.0f);
            glEnd();

            glBegin(GL_LINES);
            glVertex3f(i*ratio, 10, 0.0f);
            glVertex3f(i*ratio, -10, 0.0f);
            glEnd();
            glBegin(GL_LINES);
            glVertex3f(-i*ratio, 10, 0.0f);
            glVertex3f(-i*ratio, -10, 0.0f);
            glEnd();
        }
    }
    // Even case, try to combine?
    else
    {
        double ratio = (10.0/(double)sides)*2.0;
        for(int i = 0; i < sides/2.0; i++)
        {
            glBegin(GL_LINES);
            glVertex3f(10, (ratio/2.0) + (i*ratio), 0.0f);
            glVertex3f(-10, (ratio/2.0) + (i*ratio), 0.0f);
            glEnd();
            glBegin(GL_LINES);
            glVertex3f(10, -((ratio/2.0) + (i*ratio)), 0.0f);
            glVertex3f(-10, -((ratio/2.0) + (i*ratio)), 0.0f);
            glEnd();

            glBegin(GL_LINES);
            glVertex3f(((ratio/2.0) + (i*ratio)), 10, 0.0f);
            glVertex3f(((ratio/2.0) + (i*ratio)), -10, 0.0f);
            glEnd();
            glBegin(GL_LINES);
            glVertex3f(-((ratio/2.0) + (i*ratio)), 10, 0.0f);
            glVertex3f(-((ratio/2.0) + (i*ratio)), -10, 0.0f);
            glEnd();
        }
    }
    glEndList();
    return list;
}
void GLWidget::drawMaze(GLuint p, double dx, double dy, double dz)
{
    glPushMatrix();
    glColor3f(0, 1, 0); // Green
    glTranslated(dx, dy, dz);
    glCallList(p);
    glPopMatrix();
}
GLuint GLWidget::newWall()
{
    GLuint list = glGenLists(1);
    glNewList(list, GL_COMPILE);

    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, reflectance);

    glColor3f(0, 1, 0); // Green

    double r = (10.0/sides);//2.0;
    double h = r/1.5;

    // Begin Wall
    glBegin(GL_QUADS);
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, reflectance);
    glVertex3f( r, r,-h);
    glVertex3f(-r, r,-h);
    glVertex3f(-r, r, h);
    glVertex3f( r, r, h);

    glVertex3f( r,-r, h);
    glVertex3f(-r,-r, h);
    glVertex3f(-r,-r,-h);
    glVertex3f( r,-r,-h);

    glVertex3f( r, r, h);
    glVertex3f(-r, r, h);
    glVertex3f(-r,-r, h);
    glVertex3f( r,-r, h);

    glVertex3f( r,-r,-h);
    glVertex3f(-r,-r,-h);
    glVertex3f(-r, r,-h);
    glVertex3f( r, r,-h);

    glVertex3f(-r, r, h);
    glVertex3f(-r, r,-h);
    glVertex3f(-r,-r,-h);
    glVertex3f(-r,-r, h);

    glVertex3f( r, r,-h);
    glVertex3f( r, r, h);
    glVertex3f( r,-r, h);
    glVertex3f( r,-r,-h);
    glEnd();

    glEndList();
    return list;
}
void GLWidget::drawWalls()
{
    glColor3f(0, 1, 0); // Green
    for(int i = 0; i < wallList.count(); i++)
    {
        glPushMatrix();
        glTranslated(wallList.at(i).x, wallList.at(i).y, wallList.at(i).z);
        glCallList(wall);
        glPopMatrix();
    }
}
void GLWidget::mousePressEvent(QMouseEvent *event)
{
    lastPos = event->pos();
    setCursor(Qt::ClosedHandCursor);
}
void GLWidget::mouseMoveEvent(QMouseEvent *event)
{
    setCursor(Qt::OpenHandCursor);
    int dx = event->x() - lastPos.x();
    int dy = event->y() - lastPos.y();

    if (event->buttons() & Qt::LeftButton) {
        setXRotation(xRot + 8 * dy);
        setYRotation(yRot + 8 * dx);
    } else if (event->buttons() & Qt::RightButton) {
        setXRotation(xRot + 8 * dy);
        setZRotation(zRot + 8 * dx);
    }
    lastPos = event->pos();
}
void GLWidget::setXRotation(int angle)
{
    normalizeAngle(&angle);
    if (angle != xRot) {
        xRot = angle;
        updateGL();
    }
}
void GLWidget::setYRotation(int angle)
{
    normalizeAngle(&angle);
    if (angle != yRot) {
        yRot = angle;
        updateGL();
    }
}
void GLWidget::setZRotation(int angle)
{
    normalizeAngle(&angle);
    if (angle != zRot) {
        zRot = angle;
        updateGL();
    }
}
void GLWidget::normalizeAngle(int *angle)
{
    while (*angle < 0)
        *angle += 360 * 16;
    while (*angle > 360 * 16)
        *angle -= 360 * 16;
}
