#include "imageaction.h"
#include <QColor>
#include <QDebug>
#include "fillshape.h"

void ImageAction::delete_rect(QRect rect,QImage &img,QColor color){
    QRgb c = qRgba(color.red(), color.green(), color.blue(), color.alpha());
    int w = img.width(),h = img.height();
    for (short i = rect.top(); i < rect.top() + rect.height(); i++) {
        for (short j = rect.left(); j < rect.left() + rect.width(); j++) {
            if(i<0 || j<0 || j>=w || i>=h)continue;
            img.setPixel(j, i, c);
        }
    }
}

void ImageAction::fill(int x,int y, QImage &img,QColor color){
    FillShape fs(&img,color);
    fs.fill(x,y);
}
