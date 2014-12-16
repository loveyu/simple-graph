#ifndef GRAPHMOVE_H
#define GRAPHMOVE_H
#include <QList>
#include <QLine>
#include <QRectF>
#include <QPolygonF>
#include "GraphVector.h"
class GraphMove
{
public:
    GraphMove(int x,int y);
    bool is_move(int x,int y);
    void move(QList<QLine> &line,
              QList<QRectF> &circle,
              QList<QRectF> &oval,
              QList<QRectF> &rect,
              QList<V_Triangle> &triangle,
              QList<QPolygonF> &polygon);
private :
    int x,y;
    int o_x,o_y;
    QRectF moveRectF(QRectF rect);
    QPolygonF movePolygon(QPolygonF polygon);
};

#endif // GRAPHMOVE_H
