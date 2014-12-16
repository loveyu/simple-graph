#include "graphmove.h"
#include "GraphVector.h"

GraphMove::GraphMove(int x,int y)
{
    this->x = x;
    this->y = y;
}
bool GraphMove::is_move(int x,int y){
    o_x = x-this->x;
    o_y = y-this->y;
    this->x = x;
    this->y = y;
    return true;
}
void GraphMove::move(QList<QLine> &line,
                     QList<QRectF> &circle,
                     QList<QRectF> &oval,
                     QList<QRectF> &rect,
                     QList<V_Triangle> &triangle,
                     QList<QPolygonF> &polygon){
    QList<QLine> new_line;
    QList<QRectF> list_rect;
    QList<QPolygonF> new_polygon;
    QLine _line;
    QList<V_Triangle> new_triangle;
    V_Triangle v_t;
    if(!line.isEmpty()){
        for(int i=0; i< line.length();i++){
            _line = line.at(i);
//            _line.setLine(_line.x1()+o_x,_line.y1()+o_y,_line.x2()+o_x,_line.y2()+o_y);
            _line.translate(o_x,o_y);
            new_line.append(_line);
        }
        line = new_line;
    }
    if(!circle.isEmpty()){
        list_rect.clear();
        for(int i=0; i< circle.length();i++){
            list_rect.append(moveRectF(circle.at(i)));
        }
        circle = list_rect;
    }
    if(!oval.isEmpty()){
        list_rect.clear();
        for(int i=0; i< oval.length();i++){
            list_rect.append(moveRectF(oval.at(i)));
        }
        oval = list_rect;
    }
    if(!rect.isEmpty()){
        list_rect.clear();
        for(int i=0; i< rect.length();i++){
            list_rect.append(moveRectF(rect.at(i)));
        }
        rect = list_rect;
    }
    if(!polygon.isEmpty()){
        for(int i=0; i< polygon.length();i++){
            new_polygon.append(movePolygon(polygon.at(i)));
        }
        polygon = new_polygon;
    }
    if(!triangle.isEmpty()){
        for(int i=0; i< triangle.length();i++){
            v_t = triangle.at(i);
            v_t.x1+=o_x;v_t.x2+=o_x;v_t.x3+=o_x;
            v_t.y1+=o_y;v_t.y2+=o_y;v_t.y3+=o_y;
            new_triangle.append(v_t);
        }
        triangle = new_triangle;
    }

}

QRectF GraphMove::moveRectF(QRectF rect){
    rect.translate(o_x,o_y);
    return rect;
}

QPolygonF GraphMove::movePolygon(QPolygonF polygon){
//    QPointF point;
//    QPolygonF n_l;
    polygon.translate(o_x,o_y);
//    for(int i=0; i< polygon.length();i++){
//        point = polygon.at(i);
//        point.setX(point.x()+o_x);
//        point.setY(point.y()+o_y);
//        n_l.append(point);
//    }
    return polygon;
}


