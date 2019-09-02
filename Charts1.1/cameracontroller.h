#ifndef CAMERACONTROLLER_H
#define CAMERACONTROLLER_H

#include <Qt3DExtras>
#include <Qt3DRender>
#include <Qt3DCore>

const double DegToRad = 3.141592653589793 / 180.0;

class CameraController: public QObject
{
    Q_OBJECT

public:
    CameraController(class MainWindow *window);

    void InitCamera();
    void InitLight();
    void mouseMove(QMouseEvent *);
    void mousePress(QMouseEvent *);
    void mouseWheel(QWheelEvent *);

private:
    MainWindow *window;
    Qt3DRender::QCamera *camera;
    Qt3DRender::QDirectionalLight *cameraLight;

    int mouse_x, mouse_y;
    double alpha = 180.0, beta = 0.0;
    double radius = 11.0;

protected:
    bool eventFilter(QObject *obj, QEvent *event) override;
};

#endif
