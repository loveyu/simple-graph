#include "painterwidget.h"
#include "ccohen_sutherland.h"
#include <QMouseEvent>
#include <QPainter>
#include <QDebug>
#include <QPen>
#include "imageaction.h"
#include <math.h>

PainterWidget::PainterWidget(QWidget *parent) :
    QWidget(parent)
{
    setMouseTracking(true);
    setFocusPolicy(Qt::StrongFocus);
    //init pen
    dash_pen.setBrush(QBrush(qRgb(100,100,100)));
    QVector<qreal> dashes;
    qreal space = 3;
    dashes << 5 << space << 5 <<space;
    dash_pen.setDashPattern(dashes);
    dash_pen.setWidth(1);
}
void PainterWidget::setMainWindow(MainWindow * win,ColorLabel *c){
    main_window = win;
    color_label = c;
}
bool PainterWidget::bitmapCheck(){
    if(!image_flag){
        QMessageBox::warning(main_window,tr("Action stop"),tr("You must convert to bitmap image."));
    }
    return image_flag;
}
void PainterWidget::paint(QPainter &painter, bool save){
    if(save && image_flag && !image_out.isNull()){
        painter.drawImage(0,0,image_out);
        return;
    }
    paint(painter);
}
void PainterWidget::paint(QPainter &painter){
    QRectF f;
    if(matrix_flag){
        painter.setMatrix(matrix);
    }
    for(int i = 0;i<list_line.length();i++){
        painter.drawLine(list_line.at(i));
    }
    for(int i = 0;i<list_circle.length();i++){
        f = list_circle.at(i);
        painter.drawEllipse(f.x()-f.width()/2,f.y()-f.height()/2,f.width(),f.height());
    }
    for(int i = 0;i<list_oval.length();i++){
        f = list_oval.at(i);
        painter.drawEllipse(f.x()-f.width()/2,f.y()-f.height()/2,f.width(),f.height());
    }
    for(int i = 0;i<list_rect.length();i++){
        painter.drawRect(list_rect.at(i));
    }
    for(int i = 0;i<list_polygon.length();i++){
        painter.drawPolygon(list_polygon.at(i));
    }
    for(int i = 0;i<list_triangle.length();i++){
        V_Triangle t = list_triangle.at(i);
        painter.drawLine(t.x1,t.y1,t.x2,t.y2);
        painter.drawLine(t.x2,t.y2,t.x3,t.y3);
        painter.drawLine(t.x1,t.y1,t.x3,t.y3);
    }
}
void PainterWidget::paintEvent(QPaintEvent *event){
    event->accept();
    QPainter painter(this);
    ActionType type = main_window->getActionType();
    if(image_flag && image_out.width()>0){
        if(matrix_flag){
            painter.setMatrix(matrix);
        }
        painter.drawImage(QRectF(0,0,image_out.width(),image_out.height()),image_out);
    }else{
        paint(painter);
    }
    painter.setMatrixEnabled(false);
    switch(type){
    case Normal:
    case O_LineCut:
        //Draw normal Rect
        if(normal_rect.x1>=0 && normal_rect.x2>=0 && normal_rect.y1>=0 && normal_rect.y2>=0
                && (normal_rect.x1!=normal_rect.x2 || normal_rect.y1!=normal_rect.y2)){
            painter.setPen(dash_pen);
            painter.drawRect(normal_rect.x2,normal_rect.y2,normal_rect.x1-normal_rect.x2,normal_rect.y1-normal_rect.y2);
        }
        break;
    case D_Line:
        if(line.x1>=0 && line.x2>=0 && line.y1>=0 && line.y2>=0
                && (line.x1!=line.x2 || line.y1!=line.y2)){
            painter.drawLine(line.x1,line.y1,line.x2,line.y2);
        }
        break;
    case D_Rect:
        if(line.x1>=0 && line.x2>=0 && line.y1>=0 && line.y2>=0
                && (line.x1!=line.x2 || line.y1!=line.y2)){
            painter.drawRect(line.x1,line.y1,line.x2-line.x1,line.y2-line.y1);
        }
        break;
    case D_Circle:
        if(circle.r!=0){
            painter.drawEllipse(circle.x-circle.r/2,circle.y-circle.r/2,circle.r,circle.r);
        }
        break;
    case D_Oval:
        if(circle.r!=0 || circle.r2!=0){
            painter.drawEllipse(circle.x-circle.r/2,circle.y-circle.r2/2,circle.r,circle.r2);
        }
        break;
    case D_Triangle:
        switch(triangle_count){
        case 1:
            if(triangle.x1>=0 && triangle.x2>=1){
                painter.drawLine(triangle.x1,triangle.y1,triangle.x2,triangle.y2);
            }
            break;
        case 2:
            if(triangle.x1>=0 && triangle.x2>=0 && triangle.x3>=0){
                painter.drawLine(triangle.x1,triangle.y1,triangle.x2,triangle.y2);
                painter.setPen(dash_pen);
                painter.drawLine(triangle.x2,triangle.y2,triangle.x3,triangle.y3);
                painter.drawLine(triangle.x1,triangle.y1,triangle.x3,triangle.y3);
            }
            break;
        }
        break;
    case D_Polygon:
        if(polygon.length()>1){
            //Draw Polygon
            painter.drawPolyline(polygon);
        }
        if(line.x1>=0 && line.x2>=0){
            painter.setPen(dash_pen);
            painter.drawLine(line.x1,line.y1,line.x2,line.y2);
            if(triangle_count==-1){
                painter.drawLine(QPoint(line.x2,line.y2),polygon.at(0));
            }
        }
        break;
    case O_Revolve:
    case O_Scaled:
    case M_Rotate:
    case M_Scaled:
        if(circle.x>=0&& circle.y>=0){
            painter.drawEllipse(circle.x-2,circle.y-2,4,4);
        }
        break;
    case E_Erase:
        if(circle.x>=0&& circle.y>=0 && circle.r>0){
            if(press_status){
                painter.fillRect(QRect(circle.x-circle.r,circle.y-circle.r,circle.r*2,circle.r*2),color_label->getColor());
            }else{
                painter.drawRect(circle.x-circle.r,circle.y-circle.r,circle.r*2,circle.r*2);
            }
        }
        break;
    default:
        break;
    }
}
void PainterWidget::wheelEvent(QWheelEvent *event){
    int numSteps = event->delta() / 8 / 15;
    event->accept();
    switch(main_window->getActionType()){
    case O_Revolve:
        if(graph_revolve && circle.x>=0){
            graph_revolve->revolve(0-numSteps,list_line,list_circle,list_rect,list_triangle,list_polygon);
            update(true);
        }
        break;
    case O_Scaled:
        if(graph_scaled && circle.x>=0){
            graph_scaled->scaled(0-numSteps,list_line,list_oval,list_circle,list_rect,list_triangle,list_polygon);
            update(true);
        }
        break;
    case M_Rotate:
        if(circle.x>=0){
            matrix_value+=numSteps;
            matrix = matrix_backup;
            matrix.translate(circle.x,circle.y);
            matrix.rotate(matrix_value);
            matrix.translate(0-circle.x,0-circle.y);
            update(true);
        }
        break;

    case M_Scaled:
        if(circle.x>=0){
            matrix_value*=numSteps>0?1.25:0.9;
            matrix = matrix_backup;
            matrix.translate(circle.x,circle.y);
            matrix.scale(matrix_value,matrix_value);
            matrix.translate(0-circle.x,0-circle.y);
            update(true);
        }
        break;
    default:
        break;
    }
}
void PainterWidget::mousePressEvent(QMouseEvent *event){
    int x = event->x();
    int y = event->y();
    press_status = true;
    switch(main_window->getActionType()){
    case Normal:
    case O_LineCut:
        normal_rect.x1 = x;
        normal_rect.y1 = y;
        break;
    case D_Line:
    case D_Rect:
        line.x1 = x;
        line.y1 = y;
        break;
    case D_Circle:
    case D_Oval:
        circle.x = x;
        circle.y = y;
        circle.r = circle.r2 = 0;
        break;
    case D_Triangle:
        switch(triangle_count){
        case 0:
            triangle.x1 = x;
            triangle.y1 = y;
            triangle_count++;
            break;
        case 1:
            triangle_count++;
            break;
        case 2:
            triangle_count=0;
            list_triangle.append(triangle);
            triangle = {-1,-1,-1,-1,-1,-1};
            break;
        }
        break;
    case D_Polygon:
        line.x1 = x;
        line.y1 = y;
        polygon.append(QPointF(x,y));
        if(triangle_count==-1){
            //ADD
            list_polygon.append(polygon);
            update(true);
            polygon.clear();
            line.x1=-1;
            line.x2=-1;
        }
        triangle_count++;
        break;
    case O_Move:
        setCursor(Qt::ClosedHandCursor);
        graph_move = new GraphMove(x,y);
        break;
    case M_Move:
        line.x1 = x;
        line.y1 = y;
        matrix_backup = matrix;
        setCursor(Qt::ClosedHandCursor);
        break;
    case O_Revolve:
        graph_revolve->setTranslate(x,y);
        circle.x = x;
        circle.y = y;
        break;
    case O_Scaled:
        graph_scaled->setTranslate(x,y);
        circle.x = x;
        circle.y = y;
        break;
    case M_Rotate:
    case M_Scaled:
        matrix_backup = matrix;
        circle.x = x;
        circle.y = y;
        break;
    case E_Erase:
        ImageAction::delete_rect(QRect(circle.x-circle.r,circle.y-circle.r,circle.r*2,circle.r*2),image_out,color_label->getColor());
        update();
        break;
    case E_Fill:
        ImageAction::fill(x,y,image_out,color_label->getColor());
        update();
        break;
    default:
        break;
    }
}
void PainterWidget::mouseReleaseEvent(QMouseEvent *event){
    event->accept();
    press_status = false;
    switch(main_window->getActionType()){
    case Normal:
        normal_rect.x1 = -1;
        normal_rect.y1 = -1;
        break;
    case D_Line:
        list_line.append(QLine(line.x1,line.y1,line.x2,line.y2));
        line.x1 = -1;
        line.x2 = -1;
        break;
    case D_Rect:
        list_rect.append(QRectF(line.x1,line.y1,line.x2-line.x1,line.y2-line.y1));
        line.x1 = -1;
        line.x2 = -1;
        break;
    case D_Circle:
        list_circle.append(QRectF(circle.x,circle.y,circle.r,circle.r));
        circle.r = 0;
        break;
    case D_Oval:
        list_oval.append(QRectF(circle.x,circle.y,circle.r,circle.r2));
        circle.r =circle.r2=0;
        break;
    case O_LineCut:
        //Line Cut
        line_cs = new CCohen_Sutherland((normal_rect));
        line_cs->cutLine(list_line);
        delete line_cs;
        //reset
        normal_rect.x1 = -1;
        normal_rect.y1 = -1;
        break;
    case O_Move:
        setCursor(Qt::ArrowCursor);
        delete graph_move;
        break;
    case M_Move:
        setCursor(Qt::ArrowCursor);
        matrix_backup = matrix;
        break;
    default:
        break;
    }
    update(true);
}
void PainterWidget::mouseMoveEvent(QMouseEvent *event){
    int x = event->x();
    int y = event->y();
    ActionType type = main_window->getActionType();
    main_window->status_mouse->setText(QString("%1:%2").arg(x).arg(y));
    if(!press_status){
        if(type!=E_Erase && (triangle_count==0 || (type!=D_Triangle && type!=D_Polygon))){
            return;
        }
    }
    switch(type){
    case Normal:
    case O_LineCut:
        normal_rect.x2 = x;
        normal_rect.y2 = y;
        break;
    case D_Line:
    case D_Polygon:
        line.x2 = x;
        line.y2 = y;
        break;
    case D_Rect:
        line.x2 = x;
        line.y2 = y;
        if(press_shift){
            //width=height
            if(abs(line.x2-line.x1)<abs(line.y2-line.y1)){
                x = x-line.x1;
                if(x>0){
                    if(line.y1>y){
                        line.y2 = line.y1-x;
                    }else{
                        line.y2 = line.y1+x;
                    }
                }else{
                    if(line.y1>y){
                        line.y2 = line.y1+x;
                    }else{
                        line.y2 = line.y1-x;
                    }
                }
            }else{
                y = y-line.y1;
                if(y>0){
                    if(line.x1>x){
                        line.x2 = line.x1-y;
                    }else{
                        line.x2 = line.x1+y;
                    }
                }else{
                    if(line.x1>x){
                        line.x2 = line.x1+y;
                    }else{
                        line.x2 = line.x1-y;
                    }
                }
            }
        }
        break;
    case D_Circle:
        circle.r = sqrt((double)(x-circle.x)*(x-circle.x)*2)*2;
        break;
    case D_Oval:
        circle.r = sqrt((double)(x-circle.x)*(x-circle.x)*2)*2;
        circle.r2 = (y-circle.y)*2;
        break;
    case D_Triangle:
        switch(triangle_count){
        case 1:
            triangle.x2 = x;
            triangle.y2 = y;
            break;
        case 2:
            triangle.x3 = x;
            triangle.y3 = y;
            break;
        }
        break;
    case O_Move:
        if(graph_move->is_move(x,y)){
            graph_move->move(list_line,list_circle,list_oval,list_rect,list_triangle,list_polygon);
        }
        break;
    case M_Move:
        matrix = matrix_backup;
        matrix.translate(x-line.x1,y-line.y1);
        break;
    case E_Erase:
        circle.x = x;
        circle.y = y;
        if(press_status){
            ImageAction::delete_rect(QRect(circle.x-circle.r,circle.y-circle.r,circle.r*2,circle.r*2),image_out,color_label->getColor());
        }
        break;
    default:
        break;
    }
    if(type==O_Move){
        update(true);
    }else{
        update();
    }
}
void PainterWidget::keyPressEvent(QKeyEvent  *event){
    if(event->key()==Qt::Key_Shift){
        press_shift = true;
    }
    if(event->key()==Qt::Key_Escape && main_window->getActionType()==D_Polygon){
        triangle_count=-1;
    }
}
void PainterWidget::keyReleaseEvent(QKeyEvent *event){
    if(event->key()==Qt::Key_Shift){
        press_shift = false;
    }
}
void PainterWidget::clear(){
    list_line.clear();
    list_circle.clear();
    list_oval.clear();
    list_rect.clear();
    list_triangle.clear();
    list_polygon.clear();
    update();
}
bool PainterWidget::vectorToBitmap(){
    if(!image_flag){
        //now is vector
        image_out = QImage(width(),height(),QImage::Format_ARGB32);
        QPainter painter(&image_out);
        paint(painter);
        clear();
    }else{
        //now is bitmap
        image_out = QImage();
        update();
    }
    image_flag = !image_flag;
    return image_flag;
}
void PainterWidget::update(){
    QWidget::update();
}
void PainterWidget::update(bool up_img){
    if(image_flag && up_img){
        QPainter painter(&image_out);
        paint(painter);
        clear();
    }
    QWidget::update();
}
void PainterWidget::setActionType(ActionType type){
    if(graph_revolve!=NULL){
        delete graph_revolve;
        graph_revolve = NULL;
    }
    if(graph_scaled!=NULL){
        delete graph_scaled;
        graph_scaled = NULL;
    }
    switch(type){
    case D_Line:
        line = {0,0,0,0};
        break;
    case D_Triangle:
        triangle = {-1,-1,-1,-1,-1,-1};
    case D_Polygon:
        polygon.clear();
        triangle_count = 0;
        break;
    case O_Revolve:
        circle = {-1,-1,-1,-1};
        graph_revolve = new GraphRevolve();
        break;
    case O_Scaled:
        circle = {-1,-1,-1,-1};
        graph_scaled = new GraphScaled();
        break;
    case M_Reset:
        matrix_flag = false;
        matrix=matrix_backup = QMatrix();
        update();
        break;
    case M_Move:
    case M_Rotate:
        matrix_value = 0;
        matrix_flag = true;
        circle = {-1,-1,-1,-1};
        update();
        break;
    case M_Scaled:
        matrix_value = 1;
        matrix_flag = true;
        circle = {-1,-1,-1,-1};
        update();
        break;
    default:
        break;
    }
    line.x1=-1;
    line.x2=-1;
}

 void PainterWidget::setCircleR(int r,int r2){
     switch (main_window->getActionType()) {
     case E_Erase:
         circle.r = r;
         circle.r2 = r2;
         break;
     default:
         break;
     }
 }
