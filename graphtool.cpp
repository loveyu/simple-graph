#include "graphtool.h"
#include "painterwidget.h"

GraphTool::GraphTool(QWidget *parent) :
    QToolBar(parent)
{
    main = (MainWindow *)parent;
    spin_box = new QSpinBox();
    spin_box->setRange(1,1000);
    spin_box->setPrefix(tr("Radius:"));
    spin_box->setToolTip(tr("Radius"));
    connect(spin_box,SIGNAL(valueChanged(int)),this,SLOT(setSpinBox(int)));
    color_box = new ColorLabel(this);
}

void GraphTool::init(){
    spin_action = addWidget(spin_box);
    color_action = addWidget(color_box);
    spin_action->setVisible(false);
    addAction(spin_action);
    addAction(color_action);
}

ColorLabel * GraphTool::getColor(){
    return color_box;
}

void GraphTool::setSpinBox(int value){
    switch(main->getActionType()){
    case E_Erase:
        ((PainterWidget *)main->getPainterWidget())->setCircleR(value,value);
        break;
    default:
        break;
    }
}

void GraphTool::setAction(ActionType type,void *value){
    spin_action->setVisible(false);
    int *v;
    switch (type) {
    case E_Erase:
        v = (int *)value;
        spin_box->setValue(*v);
        spin_action->setVisible(true);
        break;
    default:
        break;
    }
}

GraphTool::~GraphTool()
{
    delete spin_box;
    delete color_box;
}
