#ifndef GRAPHTOOL_H
#define GRAPHTOOL_H
#include <QToolBar>
#include <QSpinBox>
#include <QComboBox>
#include <mainwindow.h>
#include <QAction>
#include "colorlabel.h"

class GraphTool : public QToolBar
{
    Q_OBJECT
public:
    explicit GraphTool(QWidget *parent = 0);
    ~GraphTool();
    void setAction(ActionType type,void *value);
    void init();
    ColorLabel * getColor();
public slots:
    void setSpinBox(int value);
private:
    QSpinBox *spin_box=NULL;
    ColorLabel *color_box=NULL;
    MainWindow *main;
    QAction *spin_action;
    QAction *color_action;
};

#endif // GRAPHTOOL_H
