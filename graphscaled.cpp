#include "graphscaled.h"

GraphScaled::GraphScaled()
{
    x=y=0;
}

GraphScaled::~GraphScaled()
{

}

void GraphScaled::setTranslate(int x, int y){
    this->x = x;
    this->y = y;
}

void GraphScaled::scaled(double re,QList<QLine> &line,
             QList<QRectF> &oval,
             QList<QRectF> &circle,
             QList<QRectF> &rect,
             QList<V_Triangle> &triangle,
             QList<QPolygonF> &polygon){
    matrix = QMatrix();
    matrix.translate(x,y);
    re=re>0?1.25:0.9;
    matrix.scale(re,re);
    matrix.translate(0-x,0-y);
    QList<QLine> new_line;
    QList<QRectF> list_rect;
    QList<QPolygonF> new_polygon;
    QLine _line;
    QRectF _rectf;
    QPolygonF _polygonf;
    if(!line.isEmpty()){
        for(int i=0; i< line.length();i++){
            _line = line.at(i);
            _line=matrix.map(_line);
            new_line.append(_line);
        }
        line = new_line;
    }
    if(!circle.isEmpty()){
        list_rect.clear();
        for(int i=0; i< circle.length();i++){
            _rectf = circle.at(i);
            _rectf = matrix.mapRect(_rectf);
            list_rect.append(_rectf);
        }
        circle = list_rect;
    }
    if(!oval.isEmpty()){
        list_rect.clear();
        for(int i=0; i< oval.length();i++){
            _rectf = oval.at(i);
            _rectf = matrix.mapRect(_rectf);
            list_rect.append(_rectf);
        }
        oval = list_rect;
    }
    if(!rect.isEmpty()){
        list_rect.clear();
        for(int i=0; i< rect.length();i++){
            _rectf = rect.at(i);
            _rectf = matrix.mapRect(_rectf);
            list_rect.append(_rectf);
        }
        rect = list_rect;
    }
    if(!triangle.isEmpty()){
        triangleAddQPolygonF(triangle,polygon);
        triangle.clear();
    }
    if(!polygon.isEmpty()){
        for(int i=0; i< polygon.length();i++){
            _polygonf = polygon.at(i);
            _polygonf = matrix.map(_polygonf);
            new_polygon.append(_polygonf);
        }
        polygon = new_polygon;
    }
}

void GraphScaled::triangleAddQPolygonF(QList<V_Triangle> triangle,QList<QPolygonF> &polygon){
    V_Triangle v;
    for(int i = 0;i<triangle.length();i++){
        v = triangle.at(i);
        QPolygonF p = QPolygonF();
        p.append(QPoint(v.x1,v.y1));
        p.append(QPoint(v.x2,v.y2));
        p.append(QPoint(v.x3,v.y3));
        polygon.append(p);
    }
}
