#ifndef MYOPENGL_H
#define MYOPENGL_H
#include "ActionType.h"

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QMatrix4x4>
#include <QQuaternion>
#include <QVector2D>
#include <QBasicTimer>
#include <QOpenGLShaderProgram>
#include <QOpenGLTexture>
#include <QMouseEvent>
#include <QTimerEvent>

#include "tddraw.h"

class MyOpenGL : public QOpenGLWidget
{
    Q_OBJECT
public:
    explicit MyOpenGL(QWidget *parent = 0);
    ~MyOpenGL();
    void setActionType(ActionType type);
protected:
    void mousePressEvent(QMouseEvent *e) Q_DECL_OVERRIDE;
    void mouseReleaseEvent(QMouseEvent *e) Q_DECL_OVERRIDE;
    void timerEvent(QTimerEvent *e) Q_DECL_OVERRIDE;

    void initializeGL();
    void paintGL();
    void resizeGL(int w, int h);
private:
    ActionType type;
    TdDraw *draw=NULL;

    QMatrix4x4 projection;
    QVector2D mousePressPosition;
    QVector3D rotationAxis;
    qreal angularSpeed;
    QQuaternion rotation;
    QBasicTimer timer;
};

#endif // MYOPENGL_H
