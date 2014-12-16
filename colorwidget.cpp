#include "colorwidget.h"

ColorWidget::ColorWidget(QWidget *parent) : QWidget(parent)
{
    resize(parent->width(),parent->height());
}

ColorWidget::~ColorWidget()
{

}

void ColorWidget::paintEvent(QPaintEvent *){
   QPainter painter(this);
   painter.fillRect(this->rect(),Qt::SolidPattern);
}
