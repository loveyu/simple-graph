#ifndef COLORLABEL_H
#define COLORLABEL_H

#include <QLabel>
#include <QMouseEvent>
#include <QPainter>

class ColorLabel : public QLabel
{
    Q_OBJECT
public:
    explicit ColorLabel(QWidget *parent = 0);
    ~ColorLabel();
    void setColor(QColor color);
    QColor getColor();
protected:
    void mousePressEvent(QMouseEvent *e);
    void paintEvent(QPaintEvent *e);
    QWidget *parent;
    QColor color;
};

#endif // COLORLABEL_H
