#ifndef PAINTERWIDGET_H
#define PAINTERWIDGET_H

#include "mainwindow.h"
#include "GraphVector.h"
#include "ccohen_sutherland.h"
#include "graphmove.h"
#include "graphrevolve.h"
#include "graphscaled.h"
#include <QWidget>
#include <QList>
#include <QPen>
#include "colorlabel.h"
#include <QMessageBox>
using namespace std;

class PainterWidget : public QWidget
{
    Q_OBJECT
public:
    explicit PainterWidget(QWidget *parent = 0);
    void setActionType(ActionType type);
    void clear();
    void paint(QPainter &painter);
    void paint(QPainter &painter,bool save);
    bool vectorToBitmap();
    bool bitmapCheck();
    void setCircleR(int r,int r2);
    void setMainWindow(MainWindow * win,ColorLabel *c);
signals:
protected:
    void paintEvent(QPaintEvent *event);
    void wheelEvent(QWheelEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
    void update();
    void update(bool up_img);
private:
    MainWindow * main_window;
    QList<QLine> list_line;
    QList<QRectF> list_circle;
    QList<QRectF> list_oval;
    QList<QRectF> list_rect;
    QList<V_Triangle> list_triangle;
    QList<QPolygonF> list_polygon;
    CCohen_Sutherland *line_cs;
    GraphMove *graph_move;
    GraphRevolve *graph_revolve=NULL;
    GraphScaled *graph_scaled=NULL;
    QPolygonF polygon;
    V_Line line;
    V_Line normal_rect;
    V_Circle circle;
    V_Triangle triangle;
    int triangle_count=0;
    bool press_status=false;
    bool press_shift = false;
    QPen dash_pen;
    double matrix_value;
    QMatrix matrix,matrix_backup;
    bool matrix_flag=false;
    QImage image_out;
    bool image_flag=false;
    ColorLabel *color_label;
};

#endif // PAINTERWIDGET_H
