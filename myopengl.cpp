#include "myopengl.h"
#include <QDebug>
#include <GL/glu.h>
#include <QColor>

MyOpenGL::MyOpenGL(QWidget *parent):
    QOpenGLWidget(parent)
{
}

MyOpenGL::~MyOpenGL()
{
    if(draw!=NULL){
        delete draw;
        draw = NULL;
    }
}

//! [0]
void MyOpenGL::mousePressEvent(QMouseEvent *e)
{
    // Save mouse press position
    mousePressPosition = QVector2D(e->localPos());
}

void MyOpenGL::mouseReleaseEvent(QMouseEvent *e)
{
    // Mouse release position - mouse press position
    QVector2D diff = QVector2D(e->localPos()) - mousePressPosition;

    // Rotation axis is perpendicular to the mouse position difference
    // vector
    QVector3D n = QVector3D(diff.y(), diff.x(), 0.0).normalized();

    // Accelerate angular speed relative to the length of the mouse sweep
    qreal acc = diff.length() / 100.0;

    // Calculate new rotation axis as weighted sum
    rotationAxis = (rotationAxis * angularSpeed + n * acc).normalized();

    // Increase angular speed
    angularSpeed += acc;
}
//! [0]

//! [1]
void MyOpenGL::timerEvent(QTimerEvent *)
{
    // Decrease angular speed (friction)
    angularSpeed *= 0.99;

    // Stop rotation when speed goes below threshold
    if (angularSpeed < 0.01) {
        angularSpeed = 0.0;
    } else {
        // Update rotation
        rotation = QQuaternion::fromAxisAndAngle(rotationAxis, angularSpeed) * rotation;

        // Request an update
        update();
        //qDebug() << angularSpeed;
    }
}
//! [1]

void MyOpenGL::paintGL(){
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    QMatrix4x4 matrix;
    matrix.rotate(rotation);

    switch (type) {
    case TD_Cube:
        draw->Cube(projection*matrix);
        break;
    case TD_Vertebral:
        draw->Vertebral(projection*matrix);
        break;
    default:
        draw->Default(projection*matrix);
        break;
    }
}
void MyOpenGL::initializeGL(){
    glShadeModel( GL_SMOOTH );
    glClearColor( 0.0, 0.0, 0.0, 0.0 );
    glClearDepth( 1.0 );
    glEnable( GL_DEPTH_TEST );
    glDepthFunc( GL_LEQUAL );
    glHint( GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST );

    timer.start(12, this);
}

void MyOpenGL::resizeGL(int w, int h){
    if ( h == 0 )
    {
        h = 1;
    }
    glViewport( 0, 0, (GLint)w, (GLint)h );
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    gluPerspective( 45.0, (GLfloat)w/(GLfloat)h, 0.1, 100.0 );
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();
}


void MyOpenGL::setActionType(ActionType type){
    projection = QMatrix4x4();
    this->type = type;
    update();
}
