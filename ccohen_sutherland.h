#ifndef CCOHEN_SUTHERLAND_H
#define CCOHEN_SUTHERLAND_H
#include "GraphVector.h"
#include <QList>
#include <QLine>

#define CLIP_CODE_C        0x0000
#define CLIP_CODE_W        0x0001
#define CLIP_CODE_E        0x0002
#define CLIP_CODE_S        0x0004
#define CLIP_CODE_N        0x0008
#define CLIP_CODE_SW       0x0005
#define CLIP_CODE_SE       0x0006
#define CLIP_CODE_NW       0x0009
#define CLIP_CODE_NE       0x000a

class CCohen_Sutherland
{
public:
    CCohen_Sutherland(V_Line rect);
    void cutLine(QList<QLine> &list_line);
private:
    V_Line rect;
    int cut(int LineX1,int LineY1,int LineX2,int LineY2 ,
             int RectX1,int RectY1,int RectX2,int RectY2 ,
             int &LineX3,int &LineY3,int &LineX4,int &LineY4 );
};


#endif // CCOHEN_SUTHERLAND_H
