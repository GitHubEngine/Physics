#include "models.h"
#include "plot.h"

Model7::Model7()
{
    A0 = 0.;   // Амплитуда
    angle = A0;
    h = 0.51;    //высота планки
    m = 0.5;    //масса груза
    ent = new Qt3DCore::QEntity();
    inf =  new QVBoxLayout();
    set =  new QVBoxLayout();
    LoadModel();

    tr1->setTranslation(QVector3D(0., 0.1 + h * 1.4, 0.));


    {
        QLabel *k = new QLabel(QString("Начальный угол отклонения: %1 град").arg(A0 * toGrad));
        s1 = new QSlider(Qt::Horizontal); s1->setMinimum(-150); s1->setMaximum(0); s1->setValue(int(A0 * toGrad));
        connect(s1, &QSlider::valueChanged, [=]()
        {
        A0 = double(s1->value()) * 0.1 / toGrad;
        angle = A0;
        k->setText(QString("Начальный угол отклонения: %1 рад").arg(A0));
        Transform();
        });
        set->addWidget(k);
        set->addWidget(s1);
    }
    {
        QLabel *k = new QLabel(QString("Высота планки с препятствием: %1 м").arg(h));
        s2 = new QSlider(Qt::Horizontal); s2->setMinimum(20); s2->setMaximum(90); s2->setValue(int(h * 100.));
        connect(s2, &QSlider::valueChanged, [=]()
        {
        h = double(s2->value()) * 0.01;
        k->setText(QString("Высота планки: %1 м").arg(h));
        tr1->setTranslation(QVector3D(0., 0.1 + h * 1.4, 0.));
        Transform();

        });
        set->addWidget(k);
        set->addWidget(s2);
    }
    {
        QLabel *k = new QLabel(QString("Масса груза: %1 кг").arg(m));
        s3 = new QSlider(Qt::Horizontal); s3->setMinimum(50); s3->setMaximum(1000); s3->setValue(int(m * 100.));
        connect(s3, &QSlider::valueChanged, [=]()
        {
        m = double(s3->value()) * 0.01;
        k->setText(QString("Масса груза: %1 кг").arg(m));
        });
        set->addWidget(k);
        set->addWidget(s3);
    }

}

void Model7::Compute_left()
{
    angle = A0 * cos(W * t1);


    velocity = -A0 * l * W * sin(W * t1);
    Ek = m * pow(velocity, 2) / 2;
    Ep = m * g * l * (1 - cos(angle));
    E = Ek + Ep;
}

// Движение "справа", сжатый маятник
void Model7::Compute_right()
{
    k = l / h;
    W1 = sqrt(g * k / l);
    angle = A0 * sqrt(k) * cos(W1 * t2);

    velocity = -A0 * sqrt(k) * h * W1 * sin(W1 * t2);
    Ek = m * pow(velocity, 2) / 2;
    Ep = m * g * h * (1 - cos(angle));
    E = Ek + Ep;
}


void Model7::Transform()
{

    if (angle < 0)
    {
        g1->setScale3D(QVector3D(1., 2. + 0.03, 1.));
        g1->setRotationX(angle * toGrad);
        g2->setScale(0.);

        gq->setRotationX(angle * toGrad);

    }
    else
    {
        g1->setRotationX(0.);
        g1->setScale3D(QVector3D(1., 1. - 2.225 * (h - 0.51), 1.));
        QMatrix4x4 matrix = g2->rotateAround(QVector3D(0., 0.7215 + (h - 0.51) * 1.4 + 0.0935, 0.), angle * toGrad , QVector3D(1., 0., 0.));
        matrix.translate(0., 1.443, 0.);
        gq->setMatrix(matrix);
        matrix.translate(0., -1.443, 0.);
        matrix.scale(1., 1. + 2.225 * (h - 0.51), 1.);
        matrix.translate(0., 1.443 * (1. - 0.1384 * (pow(h, -1.168)) * (h - 0.51)), 0.);
        g2->setMatrix(matrix);
    }
}

void Model7::LoadModel()
{
    addObject(ent, ":/Res/Room.obj", ":/Res/Room.png");
    addObject(ent, ":/Res/ceiling.obj", ":/Res/ceiling.jpg");
    addObject(ent, ":/Res/tablemetal.obj", ":/Res/tablemetal.png");

    addObject(ent, ":/Stands/Math7/base2.obj", ":/Stands/Math7/metal.jpg");
    Qt3DCore::QEntity *p1 = addObject(ent, ":/Stands/Math7/cube.obj", ":/Stands/Math7/metal.jpg");
    Qt3DCore::QEntity *p2 = addObject(ent, ":/Stands/Math7/planka.obj", ":/Stands/Math7/metal.jpg");
    Qt3DCore::QEntity *q = addObject(ent, ":/Stands/Math7/sphere.obj", ":/Stands/Math7/metal.jpg");
    Qt3DCore::QEntity *q1 = addObject(ent, ":/Stands/Math7/up_rope.obj", ":/Stands/Math7/rope.jpg");
    Qt3DCore::QEntity *q2 = addObject(ent, ":/Stands/Math7/down_rope.obj", ":/Stands/Math7/rope.jpg");


    tr1 = new Qt3DCore::QTransform();
    g1 = new Qt3DCore::QTransform();
    g2 = new Qt3DCore::QTransform();
    gq = new Qt3DCore::QTransform();
    p1->addComponent(tr1);
    p2->addComponent(tr1);
    q->addComponent(gq);
    q1->addComponent(g1);
    q2->addComponent(g2);



    tr1->setTranslation(QVector3D(0., 0.681, 0.));
    g1->setTranslation(QVector3D(0., 1.443, 0.));
    g2->setTranslation(QVector3D(0., 1.443, 0.));
    gq->setTranslation(QVector3D(0., 1.443, 0.));

}


void Model7::Init()
{
    t = 0.;
    W = sqrt(g / l);
    T_left = 2 * M_PI * sqrt(l / g);           //периоды при движении после столкновения
    T_right = 2 * M_PI * sqrt(h / g);

    t1 = 0;
    t2 = T_right / 4;
}

void Model7::Compute(double dt)
{
    t += dt;
        if (t1 < T_left / 4 || (t1 >= 3 * T_left / 4 && t1 < T_left) )
        {
             Compute_left();
             t1 += dt;
             if(t1 >= T_left)
             {
                 t1 = 0;
             }
             if(t1 >= T_left / 4)
             {
                 t2 = T_right / 4;
             }
        }
        else
        {
             Compute_right();
             t2 += dt;
             if(t2 >= 3 * T_right / 4)
             {
                 t1 = 3 * T_left / 4;
             }
        }
}

void Model7::Update(double dt)
{
    Compute(dt);
    Transform();
}

void Model7::CreatePlot(int)
{

}


void Model7::lock(bool f)
{
    s1->setEnabled(!f);
    s2->setEnabled(!f);
    s3->setEnabled(!f);
}
