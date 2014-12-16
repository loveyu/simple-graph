#ifndef FILLSHAPE_H
#define FILLSHAPE_H
#include <QImage>
#include "GraphVector.h"
#include <QStack>
#include <QColor>
class FillShape
{
public:
    FillShape(QImage *img,QColor c);
    void fill(int x,int y);
private:
    QImage *img;
    int w,h;
    QRgb color;
    QStack<XyPoint> stack;
    bool isBrim(int x,int y);
    void fillStack(XyPoint p);
};

#endif // FILLSHAPE_H
