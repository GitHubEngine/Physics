#include "models.h"
#include "plot.h"

Model6::Model6()
{
    ent = new Qt3DCore::QEntity();
    inf =  new QVBoxLayout();
    set =  new QVBoxLayout();
    LoadModel();

    QLabel *nam = new QLabel(QString("<center><big><b>%1</b></big></center>").arg(GetName()));
    nam->setWordWrap(true);

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

    i1 = new QLabel(QString("Угол октлонения %1 град").arg(0));
    i2 = new QLabel(QString("Угловая скорость %1 град/с").arg(0));
    inf->addWidget(i1);
    inf->addWidget(i2);
    set->addWidget(nam);
    set->addWidget(new QLabel(QString("Масса стрежня: %1 кг").arg(m_st0)));
    set->addWidget(new QLabel(QString("Длина стержня: %1 м").arg(l_st0)));
    QLabel *a1 = new QLabel(QString("Высота от оси вращения закреплённого диска: %1 м").arg(r2_0));
    a1->setWordWrap(true);
    set->addWidget(a1);

    start.push_back(0.78);
    start.push_back(0);

    {
        QLabel *k = new QLabel(QString("Начальный угол отклонения: %1 град").arg(start[0] * toGrad));
        s1 = new QSlider(Qt::Horizontal); s1->setMinimum(-450); s1->setMaximum(450); s1->setValue(int(start[0] * toGrad * 10));
        connect(s1, &QSlider::valueChanged, [=]()
        {
        start[0] = double(s1->value()) / (10 * toGrad);
        k->setText(QString("Начальный угол отклонения: %1 град").arg(start[0] * toGrad));
        Transform();
        });
        set->addWidget(k);
        set->addWidget(s1);
    }

    {
        QLabel *k = new QLabel(QString("Начальная угловая скорость: %1 град/c").arg(start[1] * toGrad));
        s2 = new QSlider(Qt::Horizontal); s2->setMinimum(-3600); s2->setMaximum(3600); s2->setValue(int(start[1] * toGrad * 10));
        connect(s2, &QSlider::valueChanged, [=]()
        {
        start[1] = double(s2->value()) / (10 * toGrad);
        k->setText(QString("Начальная угловая скорость: %1 град/c").arg(start[1] * toGrad));
        });
        set->addWidget(k);
        set->addWidget(s2);
    }

    {
        QLabel *k = new QLabel(QString("Масса дисков: %1 кг").arg(m_d0));
        s3 = new QSlider(Qt::Horizontal); s3->setMinimum(10); s3->setMaximum(100); s3->setValue(int(m_d0 * 100.));
        connect(s3, &QSlider::valueChanged, [=]()
        {
        m_d0 = double(s3->value()) / 100;
        k->setText(QString("Масса дисков: %1 кг").arg(m_d0));
        });
        set->addWidget(k);
        set->addWidget(s3);
    }

    {
        QLabel *k = new QLabel(QString("Радиус дисков: %1 м").arg(r_d0));
        s5 = new QSlider(Qt::Horizontal); s5->setMinimum(1); s5->setMaximum(500); s5->setValue(int(r_d0 * 1000.));
        connect(s5, &QSlider::valueChanged, [=]()
        {
        r_d0 = double(s5->value()) / 1000;
        k->setText(QString("Радиус дисков: %1 м").arg(r_d0));
        });
        set->addWidget(k);
        set->addWidget(s5);
    }

    {
        QLabel *k = new QLabel(QString("Высота от оси вращения незакреплённого диска: %1 м").arg(r1_0));
        k->setWordWrap(true);
        s4 = new QSlider(Qt::Horizontal); s4->setMinimum(5); s4->setMaximum(35); s4->setValue(int(r1_0 * 10.));
        connect(s4, &QSlider::valueChanged, [=]()
        {
        r1_0 = double(s4->value()) / 100;
        k->setText(QString("Высота от оси вращения незакреплённого диска: %1 м").arg(r1_0));
        Transform();
        });
        set->addWidget(k);
        set->addWidget(s4);
    }



}


void Model6::Transform()
{
    tr1->setRotationX(float(start[0] * toGrad));
    //tr2->setRotationX(float(Theta * toGrad));
    auto m = tr2->rotateAround(QVector3D(0.34f, 1.535f, 0.), float(start[0] * toGrad), QVector3D(1.f, 0., 0.));
    m.translate(QVector3D(0.34f, float(1.438 - 0.72 * (r1_0 * 10 - 0.5) / (3.5)), 0.));
    tr2->setMatrix(m);
}

void Model6::LoadModel()
{
    addObject(ent, ":/Res/Room.obj", ":/Res/Room.png");
    addObject(ent, ":/Res/potolok.obj", ":/Res/potolok.jpg");
    addObject(ent, ":/Res/View.obj", ":/Res/View.jpg");
    addObject(ent, ":/Res/List.obj", ":/Res/List.jpg");
    addObject(ent, ":/Res/tablemetal.obj", ":/Res/tablemetal.png");

    addObject(ent, ":/Stands/Math6/stand.obj", ":/Stands/Math6/stand_03.png");
    Qt3DCore::QEntity *rod = addObject(ent, ":/Stands/Math6/rod.obj", ":/Stands/Math6/rod.png");
    Qt3DCore::QEntity *load = addObject(ent, ":/Stands/Math6/load.obj", ":/Stands/Math6/load.png");

    tr1 = new Qt3DCore::QTransform();
    tr2 = new Qt3DCore::QTransform();
    rod->addComponent(tr1);
    load->addComponent(tr2);

    tr1->setTranslation(QVector3D(0.34f, 1.535f, 0.));
    tr2->setTranslation(QVector3D(0.34f, 1.438f, 0.));
}

std::vector<double> Model6::fun(double t, std::vector<double> y0)
{
    double s = sin(y0[0]);
    return { C*s, y0[1] };//y0[0]-альфа,y0[1]-z
}

double Model6::error(std::vector<double> yh, std::vector<double> y2h)
{
    return fabs(yh[0] - y2h[0]) + fabs(yh[1] - y2h[1]);
}

std::vector<double> Model6::Runge(double h, std::vector<double> y0, double t)
{
    std::vector <double> a = { 0, 0,0,0 };
    std::vector <double>  l = { 0, 0,0,0 };
    std::vector <double>  k = { 0, 0,0,0 };
    auto y1 = fun(t, y0);
    std::vector <double>  y01 = y0;
    k[0] = y1[1] * h;
    l[0] = y1[0] * h;

    y01[0] = y0[0] + 0.5*k[0];
    y01[1] = y0[1] + 0.5*l[0];
    y1 = fun(t, y01);
    k[1] = y1[1] * h;
    l[1] = y1[0] * h;

    y01[0] = y0[0] + 0.5*k[1];
    y01[1] = y0[1] + 0.5*l[1];
    y1 = fun(t, y01);
    k[2] = y1[1] * h;
    l[2] = y1[0] * h;

    y01[0] = y0[0] + k[1];
    y01[1] = y0[1] + l[1];
    y1 = fun(t, y01);
    k[3] = y1[1] * h;
    l[3] = y1[0] * h;

    a[0] = (k[0] + 2 * k[1] + 2 * k[2] + k[3]) / 6;
    a[1] = (l[0] + 2 * l[1] + 2 * l[2] + l[3]) / 6;

    y1 = fun(t, y0);

    for (int i = 0; i < y0.size(); i++)
    {
       y1[i] = a[i] + y0[i];

    }
    return y1;
}


void Model6::Init()
{
    m_st = m_st0; //масса стержня
    m_d = m_d0; //масса диска
    m = m_st + m_d; //масса маятника
    r_d = r_d0;
    hight = hight0;
    l_st = l_st0; //длина стержня
    r1 = r1_0; //расстояние от оси вращения до центра масс диска, который перемещается
    r2 = r2_0; //расстояние от оси вращения до центра масс неподвижного диска
    d = ((r1 + r2)*m_d + 0.5*l_st*m_st) / m; //расстояние от центра масс до точки подвеса (начало координат)
                                             //Подсчет момента инерции маятника
    Ist = m_st * (l_st*l_st / 12 + d * d); //стержня
    Id1 = 0.25*m_d*r_d*r_d + m_d * hight*hight / 12 + m_d * r1*r1; // дисков
    Id2 = 0.25*m_d*r_d*r_d + m_d * hight*hight / 12 + m_d * r2*r2;
    I = Ist + Id1 + Id2; //маятника
    C = -m * g*d/I; //просто константа для удобства
    start[0] = double(s1->value()) / (10 * toGrad);
    start[1] = double(s2->value()) / (10 * toGrad);
    t = 0;
    ih = 0;
    dh = 0.01;
}




void Model6::Compute(double h)
{
    start = step(dh, start, 1e-2, h);
    qDebug() << ih * h + h << " " << start[0] * toGrad << " " << start[1];

}

void Model6::Update(double h)
{
    t+=h;
    if (int64_t(t * 1000) % 10 == 0)
    {
        Compute(0.01);
        Transform();
        i1->setText(QString("Угол октлонения %1 град").arg(start[0] * toGrad));
        i2->setText(QString("Угловая скорость %1 град/с").arg(start[1] * toGrad));

        if (!cGraf->checkState())
            for (auto plot : plots)
                if (plot->GetState() == Plot::State::Active)
                    plot->Update();
                else
                {
                    plot->Destroy();
                    plots.removeOne(plot);
                }
    }
}

void Model6::CreatePlot(int plotID)
{
    Plot *plot = nullptr;
    double YSize;
    double a = start[0], w = start[1];
    Init();
    switch (plotID)
    {
    case 0:{
    YSize= PI;
    plot = new Plot([this]()->double{ return this->t; },
                        [this]()->double{ return this->start[0]; }, "График углового отклонения, рад",abs(YSize));

    break;}
    case 1:{
    YSize= PI;
    plot = new Plot([this]()->double{ return this->t; },
                        [this]()->double{ return this->start[1]; }, "График угловой скорости, рад/c",abs(YSize));

    break;}
    }
    start[0] = a;
    start[1] = w;
    if (plot)
    {
        plot->show();
        plots.append(plot);
    }
}

void Model6::GetMenu(QMenu *m)
{


    QAction *a1 = new QAction("Графики отклонения", m);
    QAction *a2 = new QAction("Графики скорости", m);

    m->addAction(a1);
    m->addAction(a2);
    connect(a1, &QAction::triggered, [=](){
        this->CreatePlot(0);
        if (cGraf->checkState())
            this->Update_plot(0.01,sGraf->value());
    });
    connect(a2, &QAction::triggered, [=](){
        this->CreatePlot(1);
        if (cGraf->checkState())
            this->Update_plot(0.01,sGraf->value());
    });
}

void Model6::Update_plot(double dt, int maxtime)
{
    double a = start[0], w = start[1];
    Init();
    for (int i=0;i<maxtime;i++){
        Compute(0.01);
        for (auto plot : plots)
            plot->Update();
    }
    start[0] = a;
    start[1] = w;
}

std::vector<double> Model6::step(double &h, std::vector<double> ystart,double eps, double h0)
{
    double tstart = h0 * ih;
    ++ih;
    std::vector <double> yh = ystart;
    std::vector <double> y2h;
    y2h.assign(ystart.size(), -100);
    int n = h0 / h;
    while (error(yh, y2h) > eps)
    {
       auto y1 = ystart;
       y2h = yh;
       for (int i = 1; i <= n; i++)
       {
          y1 = Runge(h, y1, i*h + tstart);
          // cout << y0 << endl;
       };
       yh = y1;
       n = 2 * n;
       h = h / 2;
    }
    h = 4 * h;
    return yh;
}

void Model6::lock(bool f)
{
    s1->setEnabled(!f);
    s2->setEnabled(!f);
    s3->setEnabled(!f);
    s4->setEnabled(!f);
    s5->setEnabled(!f);
}

