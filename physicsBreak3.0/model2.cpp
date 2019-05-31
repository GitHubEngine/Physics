#include "models.h"
#include "plot.h"

Model2::Model2()
{
    ent = new Qt3DCore::QEntity();
    inf =  new QVBoxLayout();
    set =  new QVBoxLayout();

    mass = 0.1;
    radius = 0.08;
    length = 0.2;
    psi_dot = 500;
    phi_dot = 0;
    theta_dot = 0;
    phi = 0;
    psi = 0;
    theta = 1.57;

    LoadModel();
    CalculateConstants();
    SetTransform();

    t = new QElapsedTimer();

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

    i1 = new QLabel("Угол θ: 0.0 град");
    i2 = new QLabel("Угол φ: 0.0 град");
    inf->addWidget(i1);
    inf->addWidget(i2);

    {
        QLabel *k = new QLabel(QString("Расстояние от стержня до диска: %1 м").arg(length));
        s1 = new QSlider(Qt::Horizontal); s1->setMinimum(15); s1->setMaximum(20); s1->setValue(int(length * 100.));
        connect(s1, &QSlider::valueChanged, [=]()
        {
        length = double(s1->value()) * 0.01;
        k->setText(QString("Расстояние от стержня до диска: %1 м").arg(length));
        SetTransform();
        });
        set->addWidget(k);
        set->addWidget(s1);

    }
    {
        QLabel *k = new QLabel(QString("Масса диска: %1 кг").arg(mass));
        s2 = new QSlider(Qt::Horizontal); s2->setMinimum(1); s2->setMaximum(20); s2->setValue(int(mass * 10.));
        connect(s2, &QSlider::valueChanged, [=]()
        {
        mass = double(s2->value()) * 0.1;
        k->setText(QString("Масса диска: %1 кг").arg(mass));
        });
        set->addWidget(k);
        set->addWidget(s2);
    }
    {
        QLabel *k = new QLabel(QString("Радиус диска: %1 м").arg(radius));
        s3 = new QSlider(Qt::Horizontal); s3->setMinimum(5); s3->setMaximum(8); s3->setValue(int(radius * 100.));
        connect(s3, &QSlider::valueChanged, [=]()
        {
        radius = double(s3->value()) * 0.01;
        k->setText(QString("Радиус диска: %1 м").arg(radius));
        SetTransform();
        });
        set->addWidget(k);
        set->addWidget(s3);
    }
    {
        QLabel *k = new QLabel(QString("Угловая скорость вращения диска: %1 рад/с").arg(psi_dot));
        s4 = new QSlider(Qt::Horizontal); s4->setMinimum(500); s4->setMaximum(1000); s4->setValue(int(psi_dot));
        connect(s4, &QSlider::valueChanged, [=]()
        {
        psi_dot = s4->value();
        k->setText(QString("Угловая скорость вращения диска: %1 рад/с").arg(psi_dot));
        });
        set->addWidget(k);
        set->addWidget(s4);
    }
    {
        QLabel *k = new QLabel(QString("Начальная скорость прецессии гироскопа: %1 рад/с").arg(phi_dot));
        s5 = new QSlider(Qt::Horizontal); s5->setMinimum(-30); s5->setMaximum(30); s5->setValue(int(phi_dot * 10.));
        connect(s5, &QSlider::valueChanged, [=]()
        {
        phi_dot = double(s5->value()) * 0.1;
        k->setText(QString("Начальная скорость прецессии гироскопа: %1 рад/с").arg(phi_dot));
        });
        set->addWidget(k);
        set->addWidget(s5);
    }
    {
        QLabel *k = new QLabel(QString("Угол отклонения от вертикальной оси: %1 рад").arg(theta));
        s6 = new QSlider(Qt::Horizontal); s6->setMinimum(785); s6->setMaximum(1570); s6->setValue(int(theta * 1000));
        connect(s6, &QSlider::valueChanged, [=]()
        {
        theta = double(s6->value()) * 0.001;
        k->setText(QString("Угол отклонения от вертикальной оси: %1 рад").arg(theta));
        SetTransform();
        });
        set->addWidget(k);
        set->addWidget(s6);
    }




}


void Model2::SetTransform()
{
    diskPos = QVector3D(cos(PI / 2 - theta)*sin(phi)*(5 * length - 1.1),
    0.95 + sin(PI / 2 - theta)*(5 * length - 1.1),
    cos(PI / 2 - theta)*cos(phi)*(5 * length - 1.1));

    nutation = QQuaternion::fromAxisAndAngle(QVector3D(1.0, 0.0, 0.0), theta * toGrad - 90);
    tr1->setRotation(precession * nutation * rotation);
    tr2->setRotation(precession * nutation);

    tr1->setScale3D(QVector3D(3 * radius, 3 * radius, 0.3));
    tr1->setTranslation(diskPos);
}

void Model2::lock(bool b)
{
    s1->setEnabled(!b);
    s2->setEnabled(!b);
    s3->setEnabled(!b);
    s4->setEnabled(!b);
    s5->setEnabled(!b);
    s6->setEnabled(!b);
}

double Model2::dy1(double arg)
{
    double fun1 = -(L_phi - L_psi * cos(arg)) * L_psi;
    double fun2 = cos(arg) * (L_phi - L_psi * cos(arg)) * (L_phi - L_psi * cos(arg));
    double fun3 = mass * length * g * sin(arg);

    fun1 /= I0 * I0 * sin(arg);

    fun2 /= I0 * I0 * sin(arg) * sin(arg) * sin(arg);

    fun3 /= I0;

    return fun1 + fun2 + fun3;
}

double Model2::dy2(double arg)
{
    return arg;
}

double Model2::dy3(double arg)
{
    double fun1 = L_phi - L_psi * cos(arg);
    double fun2 = I0 * sin(arg) * sin(arg);

    return fun1 / fun2;
}

double Model2::dy4(double arg)
{
    double fun1 = L_psi / I_psi;
    double fun2 = phi_dot * cos(arg);

    return fun1 - fun2;
}

void Model2::Init()
{
    CalculateConstants();
    t->restart();
}

void Model2::Compute(double dt)
{
    time += dt;

    double K[4][4];

    K[0][0] = dt * dy1(theta);
    K[0][1] = dt * dy1(theta + K[0][0] / 2);
    K[0][2] = dt * dy1(theta + K[0][1] / 2);
    K[0][3] = dt * dy1(theta + K[0][2]);

    theta_dot = theta_dot + (K[0][0] + 2 * K[0][1] + 2 * K[0][2] + K[0][3]) / 6;

    K[1][0] = dt * dy2(theta_dot);
    K[1][1] = dt * dy2(theta_dot + K[1][0] / 2);
    K[1][2] = dt * dy2(theta_dot + K[1][1] / 2);
    K[1][3] = dt * dy2(theta_dot + K[1][2]);

    theta = theta + (K[1][0] + 2 * K[1][1] + 2 * K[1][2] + K[1][3]) / 6;

    phi_dot = L_phi - L_psi * cos(theta);
    phi_dot /= I0;
    phi_dot /= sin(theta);
    phi_dot /= sin(theta);

    psi_dot = L_psi / I_psi;
    psi_dot -= phi_dot * cos(theta);

    K[2][0] = dt * dy3(theta);
    K[2][1] = dt * dy3(theta + K[2][0] / 2);
    K[2][2] = dt * dy3(theta + K[2][1] / 2);
    K[2][3] = dt * dy3(theta + K[2][2]);

    phi = phi + (K[2][0] + 2 * K[2][1] + 2 * K[2][2] + K[2][3]) / 6;

    K[3][0] = dt * dy4(theta);
    K[3][1] = dt * dy4(theta + K[3][0] / 2);
    K[3][2] = dt * dy4(theta + K[3][1] / 2);
    K[3][3] = dt * dy4(theta + K[3][2]);

    psi = psi + (K[3][0] + 2 * K[3][1] + 2 * K[3][2] + K[3][3]) / 6;
}

void Model2::CalculateConstants()
{
    time = 0;
    I_psi = 0.5 * mass * radius * radius;
    I0 = mass * length * length + I_psi * 0.5;
    L_psi = I_psi * (phi_dot * cos(theta) + psi_dot);
    L_phi = I0 * phi_dot * sin(theta) * sin(theta) + L_psi * cos(theta);
}

void Model2::Transform()
{
    rotation = QQuaternion::fromAxisAndAngle(QVector3D(0.0, 0.0, 1.0),  toGrad * psi);
    precession = QQuaternion::fromAxisAndAngle(QVector3D(0.0, 1.0, 0.0), toGrad * phi);
    nutation = QQuaternion::fromAxisAndAngle(QVector3D(1.0, 0.0, 0.0), toGrad * theta - 90);
    tr1->setRotation(precession * nutation * rotation);
    tr2->setRotation(precession * nutation);
    tr3->setRotation(precession);

    diskPos = QVector3D(cos(PI / 2 - theta)*sin(phi)*(5 * length - 1.1),
    0.95 + sin(PI / 2 - theta)*(5 * length - 1.1),
    cos(PI / 2 - theta)*cos(phi)*(5 * length - 1.1));

    tr1->setTranslation(diskPos);

}

void Model2::LoadModel()
{
    addObject(ent, ":/Res/Room.obj", ":/Res/Room.png");
    addObject(ent, ":/Res/potolok.obj", ":/Res/potolok.jpg");
    addObject(ent, ":/Res/View.obj", ":/Res/View.jpg");
    addObject(ent, ":/Res/List.obj", ":/Res/List.jpg");
    addObject(ent, ":/Res/tablemetal.obj", ":/Res/tablemetal.png");

    Qt3DCore::QEntity *box = addObject(ent, ":/Stands/Math2/box.obj", ":/Stands/Math2/boxMat.png");
    Qt3DCore::QEntity *axis = addObject(ent, ":/Stands/Math2/axis.obj", ":/Stands/Math2/axisMat.png");
    Qt3DCore::QEntity *disk = addObject(ent, ":/Stands/Math2/disk.obj", ":/Stands/Math2/diskMat.png");
    Qt3DCore::QEntity *stand = addObject(ent, ":/Stands/Math2/stand.obj", ":/Stands/Math2/standMat.png");

    tr1 = new Qt3DCore::QTransform();
    tr2 = new Qt3DCore::QTransform();
    tr3 = new Qt3DCore::QTransform();
    tr4 = new Qt3DCore::QTransform();

    disk->addComponent(tr1);
    axis->addComponent(tr2);
    box->addComponent(tr3);
    stand->addComponent(tr4);


    tr1->setTranslation(QVector3D(0.0, 0.95f, 0.0));
    tr2->setTranslation(QVector3D(0.0, 0.95f, 0.0));
    tr3->setTranslation(QVector3D(0.0, 0.95f, 0.0));
    tr4->setTranslation(QVector3D(0.0, 0.95f, 0.0));

    tr1->setScale(0.25);
    tr2->setScale(0.25);
    tr3->setScale(0.25);
    tr4->setScale(0.25);
}

void Model2::Update(double dt)
{

    double delt = double(t->elapsed()) * 1e-3;
    for (int i = 0; i * 0.0001 < delt / 4; ++i)
        Compute(0.0001);
    Transform();
    t->restart();
    if (!cGraf->checkState() && (int64_t(time * 1000) % (timesPrint /5) == 0))
        for (auto plot : plots)
            if (plot->GetState() == Plot::State::Active)
                plot->Update();
            else
            {
                plot->Destroy();
                plots.removeOne(plot);
            }

    i1->setText(QString("Угол θ: %1 град").arg(this->GetTheta() * toGrad, 0, 'f', 2));
    i2->setText(QString("Угол φ: %1 град").arg(this->GetPhi() * toGrad, 0, 'f', 2));
}

void Model2::CreatePlot(int plotID)
{
    Plot *plot = nullptr;

    switch (plotID)
    {
        case 0:
            plot = new Plot([this]()->double{ return this->GetPhi(); },
                            [this]()->double{ return this->GetTheta(); },  "Угол θ, рад", PI / 2, "Угол φ, рад");
        break;
        case 1:
            plot = new Plot([this]()->double{ return this->GetTime(); },
                            [this]()->double{ return this->GetTheta(); }, "Угол θ, рад", PI / 2);
        break;
    }


    if (plot)
    {
        plot->show();
        plots.append(plot);
    }
}

void Model2::Update_plot(double dt, int maxtime)
{
    double stheta     = theta;
    double sthetadot = theta_dot;
    double sphi      = phi;
    double sphidot   = phi_dot;
    double spsi      = psi;
    Init();
    for (int i=0;i<maxtime;i++){
        for (int j=0;j<timesPrint / 5;++j)
        {
            double delt = 0.001;
            for (double i = 0; i * 1e-5 < delt; ++i)
                Compute(1e-5);
        }
        for (auto plot : plots)
            plot->Update();
    }
    theta     = stheta   ;
    theta_dot = sthetadot;
    phi       = sphi     ;
    phi_dot   = sphidot  ;
    psi       = spsi     ;
}

void Model2::GetMenu(QMenu *m)
{
    QAction *a1_1 = new QAction("График зависимости θ от φ", m);
    QAction *a1_2 = new QAction("График зависимости θ от времени", m);
    m->addAction(a1_1);
    m->addAction(a1_2);

    connect(a1_1, &QAction::triggered, [=](){
        this->CreatePlot(0);
        if (cGraf->checkState())
            this->Update_plot(0.001,sGraf->value());
    });
    connect(a1_2, &QAction::triggered, [=](){
        this->CreatePlot(1);
        if (cGraf->checkState())
            this->Update_plot(0.001,sGraf->value());
    });
}




