#ifndef GRAPHVECTOR_H
#define GRAPHVECTOR_H
#include <QVector3D>
#include <QVector2D>

struct V_Line{
    int x1,y1,x2,y2;
};

struct V_Circle{
    int x,y,r,r2;
};

struct V_Triangle{
    int x1,x2,x3,y1,y2,y3;
};

struct CP2{
    int x,y,rc;
};

struct XyPoint{
    int x,y;
};

#endif // GRAPHVECTOR_H
