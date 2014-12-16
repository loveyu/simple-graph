#ifndef IMAGEACTION_H
#define IMAGEACTION_H
#include <QImage>
#include <QRect>

class ImageAction
{
public:
    static void delete_rect(QRect rect,QImage &img,QColor color);
    static void fill(int x,int y,QImage &img,QColor color);
};

#endif // IMAGEACTION_H
