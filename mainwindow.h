#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QDoubleSpinBox>
#include <QResizeEvent>
#include "ActionType.h"
#include <QDebug>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void setActionType(ActionType type);
    ActionType getActionType();
    QLabel *status_mouse;
    QLabel *status_action;
    QWidget * getPainterWidget();
protected:
    void resizeEvent(QResizeEvent *event);
private slots:
    void on_actionLine_triggered();

    void on_actionCircle_triggered();

    void on_actionOval_triggered();

    void on_actionPolygon_triggered();

    void on_actionTriangle_triggered();

    void on_actionClear_triggered();

    void on_actionRect_triggered();

    void on_actionLineCut_triggered();

    void on_actionMove_triggered();

    void on_actionRevolve_triggered();

    void on_actionScaled_triggered();

    void on_actionSave_triggered();

    void on_actionMReset_triggered();

    void on_actionMScaled_triggered();

    void on_actionMRotate_triggered();

    void on_actionMMove_triggered();

    void on_actionToBitmap_triggered();

    void on_actionErase_triggered();

    void on_actionFill_triggered();

    void on_actionTo3D_triggered();

    void on_actionCube_triggered();

    void on_actionVertebral_triggered();

    void on_action3DRect_triggered();

    void on_actionAuthor_triggered();

    void on_actionInfo_triggered();

    void on_actionExit_triggered();

private:
    Ui::MainWindow *ui;
    ActionType action_type=Normal;
    bool is_3d=false;
    bool checkIs3D();
};

#endif // MAINWINDOW_H
