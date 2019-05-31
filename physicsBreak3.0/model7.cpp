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

    QLabel *nam = new QLabel(QString("<center><big><b>%1</b></big></center>").arg(GetName()));
    nam->setWordWrap(true);
    set->addWidget(nam);

    QLabel *lGraf = new QLabel(QString("Количество значений: %1").arg(500));
    sGraf = new QSlider(Qt::Horizontal); sGraf->setMinimum(50); sGraf->setMaximum(15000); sGraf->setValue(500);
    cGraf = new QCheckBox("Моментальное построение графиков");
    connect(sGraf, &QSlider::valueChanged, [=](int d){
        lGraf->setText(QString("Количество значений: %1").arg(d));
    });
    cGraf->setCheckState(Qt::Checked);
    connect(cGraf, &QCheckBox::stateChanged, [=](int k){
        if (k == 0)
            sGraf->setEnabled(false);
        else
            sGraf->setEnabled(true);
    });
    inf->addWidget(cGraf);
    inf->addWidget(lGraf);
    inf->addWidget(sGraf);

    tr1->setTranslation(QVector3D(0., 0.1 + h * 1.4, 0.));


    {
        QLabel *k = new QLabel(QString("Начальный угол отклонения: %1 град").arg(A0 * toGrad));
        s1 = new QSlider(Qt::Horizontal); s1->setMinimum(-300); s1->setMaximum(0); s1->setValue(int(A0 * toGrad * 10));
        connect(s1, &QSlider::valueChanged, [=]()
        {
        A0 = double(s1->value()) * 0.1 / toGrad;
        angle = A0;
        k->setText(QString("Начальный угол отклонения: %1 град").arg(A0 * toGrad));
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
    addObject(ent, ":/Res/potolok.obj", ":/Res/potolok.jpg");
    addObject(ent, ":/Res/View.obj", ":/Res/View.jpg");
    addObject(ent, ":/Res/List.obj", ":/Res/List.jpg");
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
    double PI = 3.1415;
    t = 0.;
    W = sqrt(g / l);
    T_left = 2 * PI * sqrt(l / g);           //периоды при движении после столкновения
    T_right = 2 * PI * sqrt(h / g);

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
    if (!cGraf->checkState() && (int64_t(t * 1000) % timesPrint == 0))
        for (auto plot : plots)
            if (plot->GetState() == Plot::State::Active)
                plot->Update();
            else
            {
                plot->Destroy();
                plots.removeOne(plot);
            }
}

void Model7::CreatePlot(int plotID)
{
    Plot *plot = nullptr;
    double YSize;
    double st = t;
    Init();
    switch (plotID)
    {
    case 0:{
    YSize= 2.;
    plot = new Plot([this]()->double{ return this->t; },
                        [this]()->double{ return this->velocity; }, "График линейной скорости, м/c",abs(YSize));

    break;}
    case 1:{
    YSize= Ek + Ep;
    plot = new Plot([this]()->double{ return this->t; },
                        [this]()->double{ return this->Ek; }, "График кинетической энергии, Дж",abs(YSize));

    break;}
    case 2:{
    YSize= Ek + Ep;
    plot = new Plot([this]()->double{ return this->t; },
                        [this]()->double{ return this->Ep; }, "График потенциальной энергии, Дж",abs(YSize));

    break;}
    case 3:{
    YSize= Ek + Ep;
    plot = new Plot([this]()->double{ return this->t; },
                        [this]()->double{ return Ek+Ep; }, "График полной энергии, Дж",abs(YSize));

    break;}
    }
    t = st;
    if (plot)
    {
        plot->show();
        plots.append(plot);
    }
}

void Model7::GetMenu(QMenu *m)
{
    QMenu *a1 = new QMenu("Графики энергии", m);
    QAction *a1_1 = new QAction("Кинетическая энергия", a1);
    QAction *a1_2 = new QAction("Потенциальная энергия", a1);
    QAction *a1_3 = new QAction("Полная энергия", a1);

    m->addMenu(a1);
    a1->addAction(a1_1);
    a1->addAction(a1_2);
    a1->addAction(a1_3);

    QAction *a2 = new QAction("Графики линейной скорости", m);

    m->addAction(a2);


    connect(a1_1, &QAction::triggered, [=](){
        this->CreatePlot(1);
        if (cGraf->checkState())
            this->Update_plot(0.001,sGraf->value());
    });
    connect(a1_2, &QAction::triggered, [=](){
        this->CreatePlot(2);
        if (cGraf->checkState())
            this->Update_plot(0.001,sGraf->value());
    });
    connect(a1_3, &QAction::triggered, [=](){
        this->CreatePlot(3);
        if (cGraf->checkState())
            this->Update_plot(0.001,sGraf->value());
    });
    connect(a2, &QAction::triggered, [=](){
        this->CreatePlot(0);
        if (cGraf->checkState())
            this->Update_plot(0.001,sGraf->value());
    });
}

void Model7::Update_plot(double dt, int maxtime)
{
    double st = t;
    double st1 = t1;
    double st2 = t2;
    Init();
    for (int i=0;i<maxtime;i++){
        for (int j=0;j<timesPrint;++j)
        {
            t += dt;
            Compute(dt);
        }
        for (auto plot : plots)
            plot->Update();
    }
    t = st;
    t1 = st1;
    t2 = st2;
}


void Model7::lock(bool f)
{
    s1->setEnabled(!f);
    s2->setEnabled(!f);
    s3->setEnabled(!f);
}
