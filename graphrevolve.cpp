#include "graphrevolve.h"
#include <QDebug>

GraphRevolve::GraphRevolve(){
    x=y=0;
}
void GraphRevolve::setTranslate(int x,int y){
    this->x = x;
    this->y = y;
}
void GraphRevolve::revolve(double re,QList<QLine> &line,
                           QList<QRectF> &circle,
                           QList<QRectF> &rect,
                           QList<V_Triangle> &triangle,
                           QList<QPolygonF> &polygon){
    QList<QLine> new_line;
    QList<QRectF> list_rect;
    QList<QPolygonF> new_polygon;
    QLine _line;
    QRectF _rectf;
    QPolygonF _polygonf;
    matrix = QMatrix();
    matrix.translate(x,y);
    matrix.rotate(re);
    matrix.translate(0-x,0-y);

    if(!line.isEmpty()){
        for(int i=0; i< line.length();i++){
            _line = line.at(i);
            _line = matrix.map(_line);
            new_line.append(_line);
        }
        line = new_line;
    }
    if(!circle.isEmpty()){
        list_rect.clear();
        for(int i=0; i< circle.length();i++){
            _rectf = circle.at(i);
            QPointF qf = QPointF(_rectf.x(),_rectf.y());
            int width = _rectf.height();
            qf = matrix.map(qf);
            list_rect.append(QRectF(qf.x(),qf.y(),width,width));
        }
        circle = list_rect;
    }
//    if(!oval.isEmpty()){
//        list_rect.clear();
//        for(int i=0; i< oval.length();i++){
//            _rectf = oval.at(i);
//            _rectf = matrix.mapRect(_rectf);
//            list_rect.append(_rectf);
//        }
//        oval = list_rect;
//    }
    if(!triangle.isEmpty()){
        triangleAddQPolygonF(triangle,polygon);
        triangle.clear();
    }
    if(!rect.isEmpty()){
        rectAddQPolygonF(rect,polygon);
        rect.clear();
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

void GraphRevolve::triangleAddQPolygonF(QList<V_Triangle> triangle,QList<QPolygonF> &polygon){
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
void GraphRevolve::rectAddQPolygonF(QList<QRectF> rect,QList<QPolygonF> &polygon){
    QRectF v;
    for(int i = 0;i<rect.length();i++){
        v = rect.at(i);
        QPolygonF p = QPolygonF();
        p.append(QPoint(v.x(),v.y()));
        p.append(QPoint(v.x(),v.y()+v.height()));
        p.append(QPoint(v.x()+v.width(),v.y()+v.height()));
        p.append(QPoint(v.x()+v.width(),v.y()));
        polygon.append(p);
    }
}
