#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <Qt3DExtras>
#include <Qt3DRender>
#include <Qt3DCore>
#include "cameracontroller.h"
#include "plot.h"
#include "gyroscope.h"
#include "trajectory.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void resizeEvent(QResizeEvent *) override;

    void LockSlider(bool);
    void LockButtons(bool, bool, bool);
    void LockTimerButtons(bool, bool, bool);

    void DeletePlot(Plot *);

    Qt3DCore::QEntity* addObject(QString obj, QString texture, QColor ambient, float scale = 1);

    Qt3DExtras::Qt3DWindow* GetSceneWindow() { return sceneWindow; }
    Qt3DCore::QEntity* GetbaseEntity() { return baseEntity; }

private slots:
    void Update();

    void on_start_clicked();

    void on_pause_clicked();

    void on_stop_clicked();

    void on_lengthS_valueChanged(int value);

    void on_massS_valueChanged(int value);

    void on_radiusS_valueChanged(int value);

    void on_psi_dotS_valueChanged(int value);

    void on_phi_dotS_valueChanged(int value);

    void on_thetaS_valueChanged(int value);

    void on_action_triggered();

    void on_action_2_triggered();

    void on_action_3_triggered();

    void on_action_5_triggered();

    void on_action_6_triggered();

    void on_action_7_triggered();

    void on_timerStart_clicked();

    void on_timerPause_clicked();

    void on_timerStop_clicked();

    void on_action_9_triggered();

    void on_action_8_triggered();

    void on_action_10_triggered();

private:
    Ui::MainWindow *ui;

    QWidget *sceneWidget;
    Qt3DExtras::Qt3DWindow *sceneWindow;
    Qt3DCore::QEntity *baseEntity;
    CameraController *cameraController;

    QList<Plot *> plots;
    int plotID = 0;

    Gyroscope *gyro;
    bool isGyroEnabled = false;

    QTimer *timer;  
    QElapsedTimer *elapsedTimer;

    bool isTimerEnabled = false;
    QTime time;

    Trajectory *traj;
};


#endif
