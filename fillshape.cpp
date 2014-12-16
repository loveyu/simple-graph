#include "fillshape.h"
FillShape::FillShape(QImage *img,QColor c)
{
    w = img->width();
    h = img->height();
    this->img = img;
    color = qRgba(c.red(), c.green(), c.blue(), c.alpha());
}

bool FillShape::isBrim(int x,int y){
    if(x<=0 || y<=0 || x>=w || y>=h){
        return true;
    }
    QRgb rgb =img->pixel(QPoint(x,y));
    return qAlpha(rgb)!=0 && rgb>0;
}

void FillShape::fillStack(XyPoint p){
    if(qAlpha(color)==0){
        return;
    }
    XyPoint tmp;
    img->setPixel(p.x,p.y,color);
    if(!isBrim(p.x,p.y+1)){
        tmp.x = p.x;
        tmp.y = p.y+1;
        stack.push(tmp);
    }
    if(!isBrim(p.x,p.y-1)){
        tmp.x = p.x;
        tmp.y = p.y-1;
        stack.push(tmp);
    }
    if(!isBrim(p.x-1,p.y)){
        tmp.x = p.x-1;
        tmp.y = p.y;
        stack.push(tmp);
    }
    if(!isBrim(p.x+1,p.y)){
        tmp.x = p.x+1;
        tmp.y = p.y;
        stack.push(tmp);
    }
}

void FillShape::fill(int x,int y){
    if(isBrim(x,y)){
       return;
    }
    stack.clear();
    XyPoint p;
    p.x = x;
    p.y = y;
    fillStack(p);
    while(!stack.isEmpty()){
        fillStack(stack.pop());
    }
}
