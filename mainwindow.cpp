#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QPainter>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->opengl->hide();
    ui->mainToolBar->init();
    ui->widget->setMainWindow(this,ui->mainToolBar->getColor());
    resize(800,600);
    status_action = new QLabel();
    status_mouse = new QLabel();
    statusBar()->addPermanentWidget(status_action,1);
    statusBar()->addPermanentWidget(status_mouse);
    setActionType(Normal);
}

MainWindow::~MainWindow()
{
    delete status_action;
    delete status_mouse;
    delete ui;
}

void MainWindow::setActionType(ActionType type){
    action_type = type;
    int v=0;
    QColor color;
    switch(type){
    case Normal:
        status_action->setText(tr("Normal"));
        break;

    case D_Line:
        status_action->setText(tr("Draw Line"));
        break;

    case D_Circle:
        status_action->setText(tr("Draw Circle"));
        break;

    case D_Triangle:
        status_action->setText(tr("Draw Triangle"));
        break;

    case D_Polygon:
        status_action->setText(tr("Draw Polygon"));
        break;
    case D_Oval:
        status_action->setText(tr("Draw Oval"));
        break;
    case O_LineCut:
        status_action->setText(tr("Line Cut"));
        break;
    case O_Move:
        status_action->setText(tr("Move"));
        break;
    case O_Revolve:
        status_action->setText(tr("Revolve"));
        break;
    case O_Scaled:
        status_action->setText(tr("Scaled"));
        break;
    case M_Reset:
        status_action->setText(tr("Matrix Reset"));
        break;
    case M_Move:
        status_action->setText(tr("Matrix Move"));
        break;
    case M_Rotate:
        status_action->setText(tr("Matrix Rotate"));
        break;
    case M_Scaled:
        status_action->setText(tr("Matrix Scaled"));
        break;
    case E_Erase:
        if(ui->widget->bitmapCheck()){
            status_action->setText(tr("Erase"));
            v = 5;
            ui->widget->setCircleR(v,v);
            ui->mainToolBar->setAction(E_Erase,&v);
            ui->mainToolBar->getColor()->setColor(QColor(0,0,0,0));
        }
        break;
    case E_Fill:
        if(ui->widget->bitmapCheck()){
            status_action->setText(tr("Fill"));
//            v=5;
//            ui->mainToolBar->setAction(E_Fill,&v);
            QColor c = ui->mainToolBar->getColor()->getColor();
            c.setAlpha(255);
            ui->mainToolBar->getColor()->setColor(c);
        }
        break;
    case TD_Normal:
        status_action->setText(tr("3D Mode"));
        break;
    case TD_Cube:
        status_action->setText(tr("3D Cube"));
        break;
    case TD_Vertebral:
        status_action->setText(tr("3D Vertebral"));
        break;
    default:
        status_action->setText(tr("!!!!warning!!!! unknown action"));
    }
    if(is_3d){
        ui->opengl->setActionType(type);
    }else{
        ui->widget->setActionType(type);
        if(type==M_Reset){
            setActionType(Normal);
        }
    }
}

ActionType MainWindow::getActionType(){
    return action_type;
}

void MainWindow::resizeEvent(QResizeEvent * event) {
    QSize size = event->size();
    QRect rect = QRect(1, 1, size.width() - 2, size.height() - ui->menuBar->height()-ui->mainToolBar->height() - ui->statusBar->height() - 2);
    if(!is_3d){
        ui->widget->setGeometry(rect);
    }else{
        ui->opengl->setGeometry(rect);
    }
}

void MainWindow::on_actionLine_triggered()
{
    setActionType(D_Line);
}

void MainWindow::on_actionCircle_triggered()
{
    setActionType(D_Circle);
}

void MainWindow::on_actionOval_triggered()
{
    setActionType(D_Oval);
}

void MainWindow::on_actionPolygon_triggered()
{
    setActionType(D_Polygon);
}

void MainWindow::on_actionTriangle_triggered()
{
    setActionType(D_Triangle);
}

void MainWindow::on_actionClear_triggered()
{
    ui->widget->clear();
}

void MainWindow::on_actionRect_triggered()
{
    setActionType(D_Rect);
}

void MainWindow::on_actionLineCut_triggered()
{
    setActionType(O_LineCut);
}

void MainWindow::on_actionMove_triggered()
{
    setActionType(O_Move);
}

void MainWindow::on_actionRevolve_triggered()
{
    setActionType(O_Revolve);
}

void MainWindow::on_actionScaled_triggered()
{
    setActionType(O_Scaled);
}

void MainWindow::on_actionSave_triggered()
{
    QString file = QFileDialog::getSaveFileName(this, tr("Save File"), " ", tr("Image (*.png)"));
    if(!file.isEmpty()){
        QImage image = QImage(this->ui->widget->width(),this->ui->widget->height(),QImage::Format_ARGB32);
        QPainter painter(&image);
        ui->widget->paint(painter,true);
        if(image.save(file,"png")){
            QMessageBox::information(this, tr("Save success"), tr("Save success")+"\n"+file);
        }else{
            QMessageBox::warning(this, tr("Save error"), tr("Save error\nPlease try again!")+"\n"+file);
        }
    }
}

void MainWindow::on_actionMReset_triggered()
{
    setActionType(M_Reset);
}

void MainWindow::on_actionMScaled_triggered()
{
    setActionType(M_Scaled);
}

void MainWindow::on_actionMRotate_triggered()
{
    setActionType(M_Rotate);
}

void MainWindow::on_actionMMove_triggered()
{
    setActionType(M_Move);
}

void MainWindow::on_actionToBitmap_triggered()
{
    if(ui->widget->vectorToBitmap()){
        //Set To Vector
        ui->actionToBitmap->setText(tr("ToVector"));
    }else{
        //Set To Bitmap
        ui->actionToBitmap->setText(tr("ToBitmap"));
        setActionType(Normal);
    }
}

void MainWindow::on_actionErase_triggered()
{
    setActionType(E_Erase);
}

void MainWindow::on_actionFill_triggered()
{
    setActionType(E_Fill);
}
QWidget * MainWindow::getPainterWidget(){
    return ui->widget;
}

void MainWindow::on_actionTo3D_triggered()
{
    if(is_3d){
        //to 2D
        ui->actionTo3D->setText(tr("To3D"));
        ui->opengl->hide();
        ui->widget->show();
        setActionType(Normal);
    }else{
        //to 3D
        ui->actionTo3D->setText(tr("To2D"));
        ui->widget->hide();
        ui->opengl->show();
        setActionType(TD_Normal);
    }
    is_3d = !is_3d;
    QSize size(width(),height());
    QResizeEvent sz(size,size);
    QApplication::sendEvent(this,&sz);
}

void MainWindow::on_actionCube_triggered()
{
    if(checkIs3D()){
        setActionType(TD_Cube);
    }
}

bool MainWindow::checkIs3D(){
    if(!is_3d){
        QMessageBox::warning(this,tr("Action error"),tr("Action error.\nMust swicth to 3D mode."));
    }
    return is_3d;
}

void MainWindow::on_actionVertebral_triggered()
{
    if(checkIs3D()){
        setActionType(TD_Vertebral);
    }
}

void MainWindow::on_action3DRect_triggered()
{
    if(checkIs3D()){
        setActionType(TD_Normal);
    }
}

void MainWindow::on_actionAuthor_triggered()
{
    QMessageBox::about(this, tr("About the author"), tr("loveyu\nhttp://www.loveyu.org/"));
}

void MainWindow::on_actionInfo_triggered()
{
    QMessageBox::information(this, tr("About This Programe"), tr("A simple basic image rendering tool,\n supports several 3D presentations."), QMessageBox::Ok);
}
