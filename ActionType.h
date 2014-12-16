#ifndef ACTIONTYPE_H
#define ACTIONTYPE_H

enum ActionType{
    Normal,
    D_Line,
    D_Circle,
    D_Oval,
    D_Rect,
    D_Triangle,
    D_Polygon,
    O_LineCut,
    O_Move,
    O_Revolve,
    O_Scaled,
    M_Move,
    M_Rotate,
    M_Scaled,
    M_Reset,
    E_Erase,
    E_Fill,
    TD_Normal,
    TD_Cube,
    TD_Vertebral
};

#endif // ACTIONTYPE_H
