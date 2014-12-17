#include "colorlabel.h"
#include <QDebug>
#include <QColorDialog>

ColorLabel::ColorLabel(QWidget *parent) :
    QLabel(parent)
{
    this->parent = parent;
    setText("   ");
    setStyleSheet("background-color: rgb(0, 0, 0);");
}

QColor ColorLabel::getColor(){
    return color;
}

ColorLabel::~ColorLabel()
{

}
void ColorLabel::mousePressEvent(QMouseEvent *event){
    event->accept();
    color = QColorDialog::getColor(color, this->parent,tr("Select you draw color"),QColorDialog::ShowAlphaChannel);
    setColor(color);
}

void ColorLabel::paintEvent(QPaintEvent *e){
    e->accept();
    QPainter p(this);
    p.drawRect(0,0,width()-1,height()-1);
}

void ColorLabel::setColor(QColor color){
    this->color = color;
    setStyleSheet(QString("background-color: rgba(%1, %2, %3, %4);").arg(QString::number(color.red()),
                                                                         QString::number(color.green()),
                                                                         QString::number(color.blue()),
                                                                         QString::number(color.alpha())));
    update();
}

