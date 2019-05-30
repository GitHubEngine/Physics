#include "models.h"
#include "model4/plot4.h"

using namespace physics;
Model4::Model4()
{
    root        = new Qt3DCore::QEntity;
    lab         = new physics::object(root);
    bullet      = new physics::bullet   (0.01f, root);
    pendulum    = new physics::pendulum (0.20f, bullet  , root);
    measurer    = new physics::measurer (0.01f, pendulum, root);
    B           = new QPropertyAnimation(bullet  , "time");
    P           = new QPropertyAnimation(pendulum, "time");
    M           = new QPropertyAnimation(measurer, "time");
    swing       = new QParallelAnimationGroup(root);
    shoot       = new QSequentialAnimationGroup(root);
    opt         = new QVBoxLayout;
    inf         = new QVBoxLayout;

    // init laboratry
    addObject(root, ":/Res/Room.obj", ":/Res/Room.png");
    addObject(root, ":/Res/potolok.obj", ":/Res/potolok.jpg");
    addObject(root, ":/Res/View.obj", ":/Res/View.jpg");
    QLabel *nam = new QLabel(QString("<center><big><b>%1</b></big></center>").arg(GetName()));
    nam->setWordWrap(true);
    opt->addWidget(nam);

    lab->setMesh(":/Stands/Math4/lab.obj");
    lab->setTexture(":/Stands/Math4/lab.png");
    lab->setPosition(QVector3D(0, 0, 0));

    bullet->setMesh(":/Stands/Math4/bullet.obj");
    bullet->setTexture(":/Stands/Math4/bullet.png");
    bullet->setPosition(QVector3D(-2.65f, 0.34f, 1.14f));
    bullet->setScale(0.1f);
    bullet->set_r(bullet->transform()->translation());


    pendulum->setMesh(":/Stands/Math4/pendulum_bullet.obj");    // загрузить в память, чтобы не мигало при столкновении
    pendulum->setTexture(":/Stands/Math4/pendulum_bullet.png"); // загрузить в память, чтобы не мигало при столкновении
    pendulum->setMesh(":/Stands/Math4/pendulum.obj");
    pendulum->setTexture(":/Stands/Math4/pendulum.png");
    pendulum->setPosition(QVector3D(-0.22f, 3.2f, 1.14f));
    pendulum->set_r(pendulum->transform()->translation());

    measurer->setMesh(":/Stands/Math4/measurer.obj");
    measurer->setTexture(":/Stands/Math4/measurer.png");
    measurer->setPosition(QVector3D(0.07f, 0.395f, 0.96f));
    measurer->set_r(measurer->transform()->translation());

    B->setStartValue(0);
    B->setLoopCount(1);

    P->setDuration(physics::duration * 1000); // измеряется в милисекундах
    P->setLoopCount(-1);
    P->setStartValue(0);
    P->setEndValue(physics::duration);

    M->setDuration(physics::duration * 1000);
    M->setLoopCount(-1);
    M->setStartValue(0);
    M->setEndValue(physics::duration);

    swing->addAnimation(P);
    swing->addAnimation(M);
    shoot->addPause(10);
    shoot->addAnimation(B);
    shoot->addAnimation(swing);




    // init options
    bullet_mass_label   = new QLabel("");
    pendulum_mass_label = new QLabel("");
    k_label             = new QLabel("");
    b_label             = new QLabel("");
    move_label          = new QLabel("Смещение маятника: 0.000 м");
    speed_label         = new QLabel("Скорость пули: 00.000 м/с");
    move_plot_checkbox  = new QCheckBox("Фиксировать координатную сетку на графиках");

    QObject::connect(pendulum, &physics::MaterialPoint::timeChanged, [&]() {
        QString text;
        float x = (measurer->transform()->translation() - measurer->r()).x() / 4;
        text.sprintf("Смещение маятника: %0.3f м", double(x));
        move_label->setText(text);
        text.sprintf("Скорость пули: %02.3f м/с", double(bullet->v(0).x()));
        speed_label->setText(text);
        int s = int(pendulum->getTime());
        int ms = int(1e3f * pendulum->getTime()) % 1000;
        text.sprintf("Время: %02d:%02d:%02d.%03d", s / 3600, s / 60 % 60, s % 60, ms);
    });

    bullet_mass_slider = new QSlider(Qt::Horizontal);
    bullet_mass_slider->setRange(5, 20);
    bullet_mass_slider->setSingleStep(1);
    QObject::connect(bullet_mass_slider, &QSlider::valueChanged, [&](int v) {
        bullet->set_m(float(v) / 1e3f);
        QString text;
        text.sprintf("Масса пули: %0.3f кг", double(bullet->m()));
        bullet_mass_label->setText(text);
    });
    bullet_mass_slider->setValue(12);
    bullet_mass_slider->setObjectName("bullet_mass_slider");
    pendulum_mass_slider = new QSlider(Qt::Horizontal);
    pendulum_mass_slider->setRange(250, 500);
    pendulum_mass_slider->setSingleStep(1);
    QObject::connect(pendulum_mass_slider, &QSlider::valueChanged, [&](int v) {
        pendulum->set_m(float(v) / 1e3f);
        QString text;
        text.sprintf("Масса подвеса маятника: %0.3f кг", double(pendulum->m()));
        pendulum_mass_label->setText(text);
    });
    pendulum_mass_slider->setValue(375);
    k_slider = new QSlider(Qt::Horizontal);
    k_slider->setRange(12000, 13000);
    k_slider->setSingleStep(1);
    QObject::connect(k_slider, &QSlider::valueChanged, [&](int v) {
        bullet->set_k(float(v));
        QString text;
        text.sprintf("Жёсткость пружины: %05.0f Н/м", double(bullet->k()));
        k_label->setText(text);
    });
    k_slider->setValue(12500);
    b_slider = new QSlider(Qt::Horizontal);
    b_slider->setRange(15, 25);
    b_slider->setSingleStep(1);
    QObject::connect(b_slider, &QSlider::valueChanged, [&](int v) {
        bullet->set_b(float(v) / 1e3f);
        QString text;
        text.sprintf("Деформация пружины: %01.3f м", double(bullet->b()));
        b_label->setText(text);
    });
    b_slider->setValue(20);

    move_plot_checkbox->setCheckState(Qt::CheckState::Checked);

    inf->addWidget(move_plot_checkbox);
    inf->addWidget(move_label);
    inf->addWidget(speed_label);

    opt->addWidget(bullet_mass_label);
    opt->addWidget(bullet_mass_slider);
    opt->addWidget(pendulum_mass_label);
    opt->addWidget(pendulum_mass_slider);
    opt->addWidget(k_label);
    opt->addWidget(k_slider);
    opt->addWidget(b_label);
    opt->addWidget(b_slider);


}

float Model4::get_time() const
{
    return pendulum->getTime();
}

QVBoxLayout *Model4::get_opt() const
{
    return opt;
}

QVBoxLayout *Model4::get_inf() const
{
    return inf;
}

void Model4::CreatePlot(int plotID) const
{
    Plot4 *plot = nullptr;

    switch (plotID)
    {
    case 0:{
    plot = new  Plot4(
                [this]()->double{ return double(get_time()); },
                [this]()->double{ return double(pendulum->Ek(get_time())); },
                "Время, с", "Кинетическая энергия, Дж",
                0, double(2.f * physics::T),
                0, double(1.2f * pendulum->Ek(0)));
    plot->setWindowTitle("График кинетической энергии маятника");

    break;}
    case 1:{
        plot = new Plot4(
                        [this]()->double{ return double(get_time()); },
                        [this]()->double{ return double(pendulum->Ep(get_time())); },
                        "Время, с", "Потенциальная энергия, Дж",
                        0, double(2.f * physics::T),
                        0, double(1.2f * pendulum->Ep(physics::T / 4.f)));
            plot->setWindowTitle("График потенциальной энергии маятника");

    break;}
    case 2:{
        plot = new Plot4(
                    [this]()->double{ return double(get_time()); },
                    [this]()->double{ return double(pendulum->pos(get_time()).x()); },
                    "Время, с", "Смещение относительно положения равновесия, м",
                    0, double(2.f * physics::T),
                    -double(pendulum->A),
                    double(pendulum->A));
        plot->setWindowTitle("График смещения маятника относительно положения равновесия");
    break;}
    case 3:{
        plot = new Plot4(
                    [this]()->double{ return double(get_time()); },
                    [this]()->double{ return double(pendulum->v(get_time()).length()); },
                    "Время, с", "Скорость маятника, м/с",
                    0, double(2.f * physics::T),
                    -10, 10);
        plot->setWindowTitle("График скорости маятника");
        plot->setAttribute(Qt::WidgetAttribute::WA_DeleteOnClose);
    break;}
    case 4:{
            plot = new Plot4(
                        []()->double{ return 0.; },
                        [this]()->double{ return double(bullet->b() * sqrtf(bullet->k()));},
                        "Обратный корень из массы пули, кг^(-1/2)", "Скорость пули, м/с",
                        0, 20,
                        0, 45);
            plot->setWindowTitle("График скорости пули от обратного квадратного корная массы пули");
            plot->setAttribute(Qt::WidgetAttribute::WA_DeleteOnClose);
            plot->BuildMySpecificPlot();
            connect(b_slider, &QSlider::valueChanged, plot, &Plot4::BuildMySpecificPlot);
            connect(k_slider, &QSlider::valueChanged, plot, &Plot4::BuildMySpecificPlot);
    break;}

    case 5:{
           plot = new Plot4(
                        [this]()->double{ return double(get_time()); },
                        [this]()->double{ return double(asinf(pendulum->pos(get_time()).x() / physics::l)); },
                        "Время, с", "Отклонение маятника, рад",
                        0, double(2.f * physics::T),
                        -M_PI_2, M_PI_2);
            plot->setWindowTitle("График отклонения маятника от положения равновесия");
    break;}


    case 6:{
        plot = new Plot4(
                    [this]()->double{ return double(get_time()); },
                    [this]()->double{ return double(pendulum->v(get_time()).length() / physics::l *
                                          pendulum->v(get_time()).x() /
                                      abs(pendulum->v(get_time()).x())); },
                    "Время, с", "Угловая скорость, рад/с",
                    0, double(2.f * physics::T),
                    -M_PI_2, M_PI_2);
        plot->setWindowTitle("График угловой скорости маятника");
    break;}

    }
    if (plot) {
        plot->setAttribute(Qt::WidgetAttribute::WA_DeleteOnClose);
        plot->isFixed(move_plot_checkbox->isChecked());
        QObject::connect(move_plot_checkbox, &QCheckBox::toggled, plot, &Plot4::isFixed);
        connect(pendulum, &physics::MaterialPoint::timeChanged, plot, &Plot4::Update);
        plot->show();
    }

}




void Model4::Init()
{
    //start();
}

void Model4::GetMenu(QMenu *m)
{
    QAction *p = new QAction("Cкорость пули от обратного квадратного корня из массы пули", m);
    m->addAction(p);
    connect(p, &QAction::triggered, [=](){
        this->CreatePlot(4);
    });
    QMenu *a1 = new QMenu("Графики энергии", m);
    QAction *a1_1 = new QAction("Потенциальная энергия", a1);
    QAction *a1_2 = new QAction("Кинетическая энергия", a1);

    m->addMenu(a1);
    a1->addAction(a1_1);
    a1->addAction(a1_2);

    QAction *p2 = new QAction("График отклонения маятника от положения равновесия", m);
    QAction *p3 = new QAction("График угловой скорости маятника", m);
    m->addAction(p2);
    m->addAction(p3);
    connect(p2, &QAction::triggered, [=](){
        this->CreatePlot(5);
    });
    connect(p3, &QAction::triggered, [=](){
        this->CreatePlot(6);
    });



    connect(a1_1, &QAction::triggered, [=](){
        this->CreatePlot(1);
    });
    connect(a1_2, &QAction::triggered, [=](){
        this->CreatePlot(0);
    });
}

void Model4::lock(bool)
{
    if (shoot->state() == QParallelAnimationGroup::State::Running) {
        shoot->stop();
        pendulum->setTime(0);
        pendulum->move(0);
        pendulum->setMesh(":/Stands/Math4/pendulum.obj");
        pendulum->setTexture(":/Stands/Math4/pendulum.png");
        measurer->move(0);
        bullet->move(0);
    }
    else {
        float t = physics::d / bullet->v(0).x();
        B->setDuration(int(t * 1e3f));
        B->setEndValue(t);
        shoot->start();
    }
}
