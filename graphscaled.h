#ifndef GRAPHSCALED_H
#define GRAPHSCALED_H
#include <QList>
#include <QLine>
#include <QRectF>
#include <QPolygonF>
#include <QMatrix>
#include "GraphVector.h"

class GraphScaled
{
public:
    GraphScaled();
    ~GraphScaled();
    void setTranslate(int x,int y);
    void scaled(double re,QList<QLine> &line,
                 QList<QRectF> &oval,
                 QList<QRectF> &circle,
                 QList<QRectF> &rect,
                 QList<V_Triangle> &triangle,
                 QList<QPolygonF> &polygon);
private:
    int x,y;
    QMatrix matrix;
    void triangleAddQPolygonF(QList<V_Triangle> triangle,QList<QPolygonF> &polygon);
};

#endif // GRAPHSCALED_H
