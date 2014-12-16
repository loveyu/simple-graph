#ifndef GRAPHREVOLVE_H
#define GRAPHREVOLVE_H
#include <QList>
#include <QLine>
#include <QRectF>
#include <QPolygonF>
#include <QMatrix>
#include "GraphVector.h"
class GraphRevolve
{
public:
    GraphRevolve();
    void setTranslate(int x,int y);
    void revolve(double re,QList<QLine> &line,
                 QList<QRectF> &circle,
                 QList<QRectF> &rect,
                 QList<V_Triangle> &triangle,
                 QList<QPolygonF> &polygon);
    QMatrix matrix;
private :
    int x,y;
    void triangleAddQPolygonF(QList<V_Triangle> triangle,QList<QPolygonF> &polygon);
    void rectAddQPolygonF(QList<QRectF> triangle,QList<QPolygonF> &polygon);
};

#endif // GRAPHREVOLVE_H
