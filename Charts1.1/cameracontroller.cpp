#include "cameracontroller.h"
#include "mainwindow.h"

CameraController::CameraController(MainWindow *window)
    :window(window)
{
}

void CameraController::InitCamera()
{
    camera = window->GetSceneWindow()->camera();
    camera->lens()->setPerspectiveProjection(45.0, 16.0f/9.0f, 0.1f, 40.0f);
    camera->setPosition(QVector3D(-radius, 0.0, 0.0));
    camera->setUpVector(QVector3D(0, 1, 0));
    camera->setViewCenter(QVector3D(0.0, 0.0, 0.0));
}

void CameraController::InitLight()
{
    Qt3DCore::QEntity *cameraLightEntity = new Qt3DCore::QEntity(window->GetbaseEntity());
    cameraLight = new Qt3DRender::QDirectionalLight();
    cameraLight->setColor("white");
    cameraLight->setIntensity(0.23f);
    cameraLight->setWorldDirection(-camera->position());
    cameraLightEntity->addComponent(cameraLight);

    Qt3DCore::QEntity *spotLightEntity = new Qt3DCore::QEntity(window->GetbaseEntity());
    Qt3DRender::QSpotLight *spotLight = new Qt3DRender::QSpotLight();
    spotLight->setColor("white");
    spotLight->setConstantAttenuation(1.0f);
    spotLight->setLinearAttenuation(0.027f);
    spotLight->setQuadraticAttenuation(0.02f);
    spotLight->setLocalDirection(QVector3D(0.0, -1.0, 0.0));
    spotLight->setCutOffAngle(70);

    Qt3DCore::QTransform *spotTransform = new Qt3DCore::QTransform();
    spotTransform->setTranslation({0.0, 10.0, 0.0});

    spotLightEntity->addComponent(spotLight);
    spotLightEntity->addComponent(spotTransform);
}

void CameraController::mouseMove(QMouseEvent *me)
{
    if (me->buttons() & Qt::LeftButton)
    {
        beta += (me->y() - mouse_y);
        alpha += (me->x() - mouse_x);
        mouse_x = me->x();
        mouse_y = me->y();

        if (beta > 50) beta = 50;
        if (beta < -50) beta = -50;

        QVector3D pos(cos(beta * DegToRad) * cos(alpha * DegToRad) * radius,
                      sin(beta * DegToRad) * radius,
                      cos(beta * DegToRad) * sin(alpha * DegToRad) * radius);

        camera->setPosition(pos);
        cameraLight->setWorldDirection(-pos);
    }
}

void CameraController::mousePress(QMouseEvent *me)
{
    mouse_x = me->x();
    mouse_y = me->y();
}

void CameraController::mouseWheel(QWheelEvent *we)
{
    if (we->delta() > 0)
        radius -= 0.3;
    else
        radius += 0.3;

    if (radius < 4)
        radius = 4;

    if (radius > 12)
        radius = 12;

    QVector3D pos(cos(beta * DegToRad) * cos(alpha * DegToRad) * radius,
                  sin(beta * DegToRad) * radius,
                  cos(beta * DegToRad) * sin(alpha * DegToRad) * radius);

    camera->setPosition(pos);
}

bool CameraController::eventFilter(QObject *obj, QEvent *event)
{
    if (event->type() == QEvent::MouseMove)
    {
        mouseMove(static_cast<QMouseEvent*>(event));
        return true;
    }

    if (event->type() == QEvent::MouseButtonPress)
    {
        mousePress(static_cast<QMouseEvent*>(event));
        return true;
    }

    if (event->type() == QEvent::Wheel)
    {
        mouseWheel(static_cast<QWheelEvent*>(event));
        return true;
    }

}


