#include "models.h"
#include "plot.h"

Model8::Model8()
{
    ent = new Qt3DCore::QEntity();
    inf =  new QVBoxLayout();
    set =  new QVBoxLayout();
    LoadModel();

    U = 10;
    d = 25;
    D = 2;
    L = 20;
    m = 2;
    w_lable = new QLabel(QString("Угол отклонения").arg(0));
    an_lable = new QLabel(QString("Угловая скорость").arg(0));

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


    inf->addWidget(w_lable);
    {
        QLabel *k = new QLabel(QString("Напряжение на конденсаторах: %1<sup>5</sup> B").arg(U));
        s1 = new QSlider(Qt::Horizontal); s1->setMinimum(9); s1->setMaximum(11); s1->setValue(10);
        connect(s1, &QSlider::valueChanged, [=]()
        {
        k->setText(QString("Напряжение на конденсаторах: %1<sup>5</sup> В").arg(s1->value()));
        U = s1->value();
        });
        set->addWidget(k);
        set->addWidget(s1);
    }
    {
        QLabel *k = new QLabel(QString("Расстояние между пластинами: %1 см").arg(d));
        s2 = new QSlider(Qt::Horizontal); s2->setMinimum(15); s2->setMaximum(30); s2->setValue(25);
        connect(s2, &QSlider::valueChanged, [=]()
        {
             k->setText(QString("Расстояние между пластинами: %1 см").arg(s2->value()));
             tr1->setTranslation({0. , 0., -float(s2->value())*0.02f});
             tr2->setTranslation({0. , 0., float(s2->value())*0.02f});
             d = s2->value();
             Recalculate_pos();
        //gtr1->setScale3D({1.f, float(s2->value()), 1.f});
        });
        set->addWidget(k);
        set->addWidget(s2);
    }
    {
        QLabel *k = new QLabel(QString("Диаметр шара: %1 см").arg(3));
        s3 = new QSlider(Qt::Horizontal); s3->setMinimum(1); s3->setMaximum(4); s3->setValue(2);
        connect(s3, &QSlider::valueChanged, [=]()
        {
            k->setText(QString("Диаметр шара: %1 см").arg(s3->value()));
            shar_t->setScale(s3->value()*0.5);
            D = s3->value();
            Recalculate_pos();
        });
        set->addWidget(k);
        set->addWidget(s3);
    }
    {
        QLabel *k = new QLabel(QString("Масса шара: %1 г").arg(3));
        s4 = new QSlider(Qt::Horizontal); s4->setMinimum(1); s4->setMaximum(4); s4->setValue(2);
        connect(s4, &QSlider::valueChanged, [=]()
        {
            k->setText(QString("Масса шара: %1 г").arg(s4->value()));
            m = s4->value();
        });
        set->addWidget(k);
        set->addWidget(s4);
    }
    Recalculate_pos();


}



void Model8::Transform(float angle)
{

}

void Model8::LoadModel()
{
    addObject(ent, ":/Res/Room.obj", ":/Res/Room.png");
    addObject(ent, ":/Res/ceiling.obj", ":/Res/ceiling.jpg");
    addObject(ent, ":/Res/tablemetal.obj", ":/Res/tablemetal.png");

    addObject(ent, ":/Stands/Math8/stand.obj", ":/Stands/Math8/stand.jpg");
    addObject(ent, ":/Stands/Math8/tab.obj", ":/Stands/Math8/tab.jpg");
    Qt3DCore::QEntity *p1 = addObject(ent, ":/Stands/Math8/plas.obj", ":/Stands/Math8/plas.jpg");
    Qt3DCore::QEntity *p2 = addObject(ent, ":/Stands/Math8/plas.obj", ":/Stands/Math8/plas.jpg");
    Qt3DCore::QEntity *shar = addObject(ent, ":/Stands/Math8/shar.obj", ":/Stands/Math8/plas.jpg");
    Qt3DCore::QEntity *rope = addObject(ent, ":/Stands/Math8/rope.obj", ":/Stands/Math8/rope.jpg");

    addObject(ent, ":/Stands/Math8/gen.obj", ":/Stands/Math8/gen.jpg");
    addObject(ent, ":/Stands/Math8/reg.obj", ":/Stands/Math8/reg.jpg");
    addObject(ent, ":/Stands/Math8/but.obj", ":/Stands/Math8/but.jpg");




    tr1 = new Qt3DCore::QTransform();
    tr2 = new Qt3DCore::QTransform();
    shar_t = new Qt3DCore::QTransform();
    rope_t = new Qt3DCore::QTransform();
    p1->addComponent(tr1);
    p2->addComponent(tr2);
    shar->addComponent(shar_t);
    rope->addComponent(rope_t);
    tr1->setTranslation({0. , 0., -.5f});
    tr2->setTranslation({0. , 0., .5f});
    rope_t->setTranslation({0. , 0.972f, 0. });
    shar_t->setTranslation({0. , 0.3f, 0. });


   /* tr1->setTranslation(QVector3D(0., 0.681, 0.));
    g1->setTranslation(QVector3D(0., 1.443, 0.));
    g2->setTranslation(QVector3D(0., 1.443, 0.));
    gq->setTranslation(QVector3D(0., 1.443, 0.));*/


}

void Model8::Recalculate_pos()
{
    y1 = float(d)/2 - float(D)/2;

    y2 = float(sqrt(pow(L,2)-pow(y1,2)));
    double ang = asin(float(y1)/float(L));
    angle = ang*toGrad;
    rope_t->setRotationX(float(-angle));
    y1 = y1*0.01f;
    y2 = y2*0.01f;
    shar_t->setTranslation( QVector3D(.0, 0.972f - y2*4, y1*4) );
    c_angle = -angle;
    w_lable->setText(QString("Угол отклонения: %1 град").arg(c_angle));
}
void Model8::Init()
{
    t = 0;
}

void Model8::compute(double dt)
{
    float l_U = pow(U,5);
    float l_m = m*0.001;
    float l_d = d*0.01;
    float l_D = D*0.01;
    float l_L = L*0.01;
    q = 2 * PI * e_0 * l_D * U;
    float w = 2*PI/(2*l_d*sqrt(2*l_m/(l_U*q)));

    float K1=(l_U*q)/m*d - l_m *g * tan(w*t);
    float K2=(l_U*q)/m*d - l_m *g * tan(w*(t+dt/2));
    float K3=(l_U*q)/m*d - l_m *g * tan(w*(t+dt/2));
    float K4=(l_U*q)/m*d - l_m *g * tan(w*(t+dt));
    float k1 = y2;
    float k2 = y2 + K1*dt/2;
    float k3 = y2 + K2*dt/2;
    float k4 = y2 + K3*dt;

    y1 += dt*((K1+2*K2+2*K3+K4)/6);
    y2 += dt*((k1+2*k2+2*k3+k4)/6);

}

void Model8::Update(double dt)
{
    t += dt;
    Compute(dt);
    rope_t->setRotationX(c_angle);
    shar_t->setTranslation( QVector3D(.0, 0.972f - y2*4, y1*4) );
    w_lable->setText(QString("угловая скорость: %1 рад/с").arg(w));

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

void Model8::Compute(double dt)
{
    float l_U = pow(U,5);
    float l_m = m*0.001;
    float l_d = d*0.01;
    float l_D = D*0.01;
    float l_L = L*0.01;
    q = 2 * PI * e_0 * l_D * U;
    w = 2.*PI/(2.*l_d*sqrt(2.*l_m/(l_U*q)));
    if (abs(c_angle) >= abs(angle))
    {
        if (c_angle>0) mark = -1;
        else mark = 1;
    }
    c_angle+= 2*mark*(180/PI)*w*dt;
    an_lable->setText(QString("Угол отклонения: %1 град").arg(c_angle));
    w_lable->setText(QString("Угловая скорость: %1 рад").arg(w));
    y1 = -sin(c_angle*PI/180)*l_L;
    y2 = sqrt(pow(l_L,2) - pow(y1,2));

}

double Model8::GetTime()
{
    return t;
}
double Model8::GetAngle()
{
    return c_angle*PI/180;
}
double Model8::GetW()
{
    return y1 * 4;
}
void Model8::Update_plot(double dt, int maxtime)
{
    double stime = t;
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
    t = stime;
}

void Model8::CreatePlot(int plotID)
{
    Plot *plot = nullptr;

    switch (plotID)
    {
    case 0:
        plot = new Plot([this]()->double{ return this->GetTime(); },
                        [this]()->double{ return this->GetAngle(); }, "Угловое отклонение, рад", 5);
    break;
    case 1:
        plot = new Plot([this]()->double{ return this->GetTime(); },
                        [this]()->double{ return this->GetW(); }, "Отклонение от центра, м", 1);
    break;
    }

    if (plot)
    {
        plot->show();
        plots.append(plot);
    }
}

void Model8::GetMenu(QMenu *m)
{
    QAction *a1 = new QAction("График углового отклонения", m);
    QAction *a2 = new QAction("График перемещения по оси x", m);
    m->addAction(a1);
    m->addAction(a2);

    connect(a1, &QAction::triggered, [=](){
        this->CreatePlot(0);
        if (cGraf->checkState())
            this->Update_plot(0.001,sGraf->value());
    });
    connect(a2, &QAction::triggered, [=](){
        this->CreatePlot(1);
        if (cGraf->checkState())
            this->Update_plot(0.001,sGraf->value());
    });
}
