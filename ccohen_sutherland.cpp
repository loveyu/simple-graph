#include "ccohen_sutherland.h"
#include <QLine>
#include <QRect>
#include <QDebug>

CCohen_Sutherland::CCohen_Sutherland(V_Line rect)
{
    this->rect = rect;
}

void CCohen_Sutherland::cutLine(QList<QLine> &list_line){
    QLine line;
    QList<QLine> new_lines;
    V_Line v_line;
    for(int i = 0;i<list_line.length();i++){
        line = list_line.at(i);
        switch(cut(line.x1(),line.y1(),line.x2(),line.y2(),rect.x1,rect.y1,rect.x2,rect.y2,v_line.x1,v_line.y1,v_line.x2,v_line.y2)){
        case 0:
            new_lines.append(QLine(v_line.x1,v_line.y1,v_line.x2,v_line.y2));
            break;
        case 1:
            qDebug()<<"can not cut";
            break;
        }

    }
    list_line = new_lines;
}


//裁剪直线-Conhen-Sutherland算法
int CCohen_Sutherland::cut(int LineX1,int LineY1,int LineX2,int LineY2 ,
                           int RectX1,int RectY1,int RectX2,int RectY2 ,
                           int &LineX3,int &LineY3,int &LineX4,int &LineY4 )
{


    int Code1 = 0,Code2 = 0,Temp = -1;

    LineX3 = LineX1;
    LineY3 = LineY1;
    LineX4 = LineX2;
    LineY4 = LineY2;

    if (RectX1 > RectX2)
    {
        Temp = RectX2;
        RectX2 = RectX1;
        RectX1 = Temp;
    }
    if (RectY1 > RectY2)
    {
        Temp = RectY2;
        RectY2 = RectY1;
        RectY1 = Temp;
    }

    if (LineX1 < RectX1)
    {
        Code1 |= CLIP_CODE_W;
    }
    if (LineX1 > RectX2)
    {
        Code1 |= CLIP_CODE_E;
    }
    if (LineY1 < RectY1)
    {
        Code1 |= CLIP_CODE_N;
    }
    if (LineY1 > RectY2)
    {
        Code1 |= CLIP_CODE_S;
    }
    if (LineX2 < RectX1)
    {
        Code2 |= CLIP_CODE_W;
    }
    if (LineX2 > RectX2)
    {
        Code2 |= CLIP_CODE_E;
    }
    if (LineY2 < RectY1)
    {
        Code2 |= CLIP_CODE_N;
    }
    if (LineY2 > RectY2)
    {
        Code2 |= CLIP_CODE_S;
    }

    if (Code1 & Code2)
    {
        return 1;
    }
    if (Code1==0 && Code2==0)
    {
        return 0;
    }
    switch(Code1)
    {
    case CLIP_CODE_C:
        break;
    case CLIP_CODE_W:
    {
        LineX3 = RectX1;
        LineY3 = (LineX3-LineX1)*(LineY2-LineY1)/(LineX2-LineX1) + LineY1 + 0.5;
        break;
    }
    case CLIP_CODE_E:
    {
        LineX3 = RectX2;
        LineY3 = (LineX3-LineX1)*(LineY2-LineY1)/(LineX2-LineX1) + LineY1 + 0.5;
        break;
    }
    case CLIP_CODE_S:
    {
        LineY3 = RectY2;
        LineX3 = (LineY3-LineY1)*(LineX2-LineX1)/(LineY2-LineY1) + LineX1 + 0.5;
        break;
    }
    case CLIP_CODE_N:
    {
        LineY3 = RectY1;
        LineX3 = (LineY3-LineY1)*(LineX2-LineX1)/(LineY2-LineY1) + LineX1 + 0.5;
        break;
    }
    case CLIP_CODE_SW:
    {
        LineY3 = RectY2;
        LineX3 = (LineY3-LineY1)*(LineX2-LineX1)/(LineY2-LineY1) + LineX1 + 0.5;
        if (LineX3 < RectX1)
        {
            LineX3 = RectX1;
            LineY3 = (LineX3-LineX1)*(LineY2-LineY1)/(LineX2-LineX1) + LineY1 + 0.5;
        }
        break;
    }
    case CLIP_CODE_SE:
    {
        LineY3 = RectY2;
        LineX3 = (LineY3-LineY1)*(LineX2-LineX1)/(LineY2-LineY1) + LineX1 + 0.5;
        if (LineX3 > RectX2)
        {
            LineX3 = RectX2;
            LineY3 = (LineX3-LineX1)*(LineY2-LineY1)/(LineX2-LineX1) + LineY1 + 0.5;
        }
        break;
    }
    case CLIP_CODE_NW:
    {
        LineY3 = RectY1;
        LineX3 = (LineY3-LineY1)*(LineX2-LineX1)/(LineY2-LineY1) + LineX1 + 0.5;
        if (LineX3 < RectX1)
        {
            LineX3 = RectX1;
            LineY3 = (LineX3-LineX1)*(LineY2-LineY1)/(LineX2-LineX1) + LineY1 + 0.5;
        }
        break;
    }
    case CLIP_CODE_NE:
    {
        LineY3 = RectY1;
        LineX3 = (LineY3-LineY1)*(LineX2-LineX1)/(LineY2-LineY1) + LineX1 + 0.5;
        if (LineX3 > RectX2)
        {
            LineX3 = RectX2;
            LineY3 = (LineX3-LineX1)*(LineY2-LineY1)/(LineX2-LineX1) + LineY1 + 0.5;
        }
        break;
    }
    }

    switch(Code2)
    {
    case CLIP_CODE_C:
        break;
    case CLIP_CODE_W:
    {
        LineX4 = RectX1;
        LineY4 = (LineX4-LineX1)*(LineY2-LineY1)/(LineX2-LineX1) + LineY1 + 0.5;
        break;
    }
    case CLIP_CODE_E:
    {
        LineX4 = RectX2;
        LineY4 = (LineX4-LineX1)*(LineY2-LineY1)/(LineX2-LineX1) + LineY1 + 0.5;
        break;
    }
    case CLIP_CODE_S:
    {
        LineY4 = RectY2;
        LineX4 = (LineY4-LineY1)*(LineX2-LineX1)/(LineY2-LineY1) + LineX1 + 0.5;
        break;
    }
    case CLIP_CODE_N:
    {
        LineY4 = RectY1;
        LineX4 = (LineY4-LineY1)*(LineX2-LineX1)/(LineY2-LineY1) + LineX1 + 0.5;
        break;
    }
    case CLIP_CODE_SW:
    {
        LineY4 = RectY2;
        LineX4 = (LineY4-LineY1)*(LineX2-LineX1)/(LineY2-LineY1) + LineX1 + 0.5;
        if (LineX4 < RectX1)
        {
            LineX4 = RectX1;
            LineY4 = (LineX4-LineX1)*(LineY2-LineY1)/(LineX2-LineX1) + LineY1 + 0.5;
        }
        break;
    }
    case CLIP_CODE_SE:
    {
        LineY4 = RectY2;
        LineX4 = (LineY4-LineY1)*(LineX2-LineX1)/(LineY2-LineY1) + LineX1 + 0.5;
        if (LineX4 > RectX2)
        {
            LineX4 = RectX2;
            LineY4 = (LineX4-LineX1)*(LineY2-LineY1)/(LineX2-LineX1) + LineY1 + 0.5;
        }
        break;
    }
    case CLIP_CODE_NW:
    {
        LineY4 = RectY1;
        LineX4 = (LineY4-LineY1)*(LineX2-LineX1)/(LineY2-LineY1) + LineX1 + 0.5;
        if (LineX4 < RectX1)
        {
            LineX4 = RectX1;
            LineY4 = (LineX4-LineX1)*(LineY2-LineY1)/(LineX2-LineX1) + LineY1 + 0.5;
        }
        break;
    }
    case CLIP_CODE_NE:
    {
        LineY4 = RectY1;
        LineX4 = (LineY4-LineY1)*(LineX2-LineX1)/(LineY2-LineY1) + LineX1 + 0.5;
        if (LineX4 > RectX2)
        {
            LineX4 = RectX2;
            LineY4 = (LineX4-LineX1)*(LineY2-LineY1)/(LineX2-LineX1) + LineY1 + 0.5;
        }
        break;
    }
    }

    if (LineX3<RectX1 || LineX3>RectX2
            || LineX4<RectX1 || LineX4>RectX2
            || LineY3<RectY1 || LineY4>RectY2
            || LineX4<RectY1 || LineY4>RectY2)
    {
        return 1;
    }

    return 0;
}
