#ifndef TDCUBE_H
#define TDCUBE_H
#include <QtOpenGL/qgl.h>
#include <QMatrix4x4>
class TdDraw
{
public:
    TdDraw();
    ~TdDraw();
    void Cube(QMatrix4x4 r);
    void Vertebral(QMatrix4x4 r);
    void Default(QMatrix4x4 r);
private:
    void init();
};

#endif // TDCUBE_H
