#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "drawline.h"
#include "plot.h"
#include "gyroscope.h"
#include "help.h"
#include "manual.h"
#include "about.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    sceneWindow = new Qt3DExtras::Qt3DWindow();
    sceneWindow->defaultFrameGraph()->setClearColor(QColor(QRgb(0x9fb7cf)));
    sceneWidget = QWidget::createWindowContainer(sceneWindow, ui->scene);
    sceneWidget->setGeometry(ui->scene->geometry());
    baseEntity = new Qt3DCore::QEntity();
    sceneWindow->setRootEntity(baseEntity);

    cameraController = new CameraController(this);
    cameraController->InitCamera();
    cameraController->InitLight();
    sceneWindow->installEventFilter(cameraController);

    LockButtons(true, false, false);
    LockTimerButtons(true, false, false);

    gyro = new Gyroscope(this);

    ui->massL->setText(QString("Масса диска: %1 кг").arg(ui->massS->value() * 0.1));
    ui->radiusL->setText(QString("Радиус диска: %1 м").arg(ui->radiusS->value() * 0.01));
    ui->lengthL->setText(QString("Расстояние от диска до стержня: %1 м").arg(ui->lengthS->value() * 0.01));
    ui->phi_dotL->setText(QString("Начальная скорость прецессии: %1 рад/c").arg(ui->phi_dotS->value() * 0.1));
    ui->psi_dotL->setText(QString("Скорость вращения диска: %1 рад/c").arg(ui->psi_dotS->value()));
    ui->thetaL->setText(QString("Наклон относительно вертикальной оси: %1 град").arg(round(ui->thetaS->value() * 0.001 / DegToRad)));

    timer = new QTimer();
    timer->setInterval(16);
    connect(timer, SIGNAL(timeout()), this, SLOT(Update()));
    timer->start();

    elapsedTimer = new QElapsedTimer();
    elapsedTimer->start();

    time.setHMS(0, 0, 0);
    ui->timerL->setText("Время:  " + time.toString("mm:ss:zzz"));

    addObject(":/Res/Models/table.obj", ":/Res/Models/tableMat.jpg", QColor::fromRgb(150, 150, 150));
    addObject(":/Res/Models/floor.obj", ":/Res/Models/floorMat.jpg", QColor::fromRgb(160, 160, 160), 8);

    traj = new Trajectory(baseEntity);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::resizeEvent(QResizeEvent *re)
{
    ui->horizontal->setGeometry(0, 0, re->size().width(), re->size().height());
    sceneWidget->setGeometry(ui->scene->geometry());
}

void MainWindow::LockSlider(bool value)
{
    ui->massS->setEnabled(value);
    ui->lengthS->setEnabled(value);
    ui->radiusS->setEnabled(value);
    ui->phi_dotS->setEnabled(value);
    ui->psi_dotS->setEnabled(value);
    ui->thetaS->setEnabled(value);
}

void MainWindow::LockButtons(bool start, bool pause, bool stop)
{
    ui->start->setEnabled(start);
    ui->pause->setEnabled(pause);
    ui->stop->setEnabled(stop);
}

void MainWindow::LockTimerButtons(bool start, bool pause, bool stop)
{
    ui->timerStart->setEnabled(start);
    ui->timerPause->setEnabled(pause);
    ui->timerStop->setEnabled(stop);
}

void MainWindow::Update()
{
    double dt = elapsedTimer->elapsed() * 0.001;

    if (isGyroEnabled)
    {
        for(int i = 0; i * 0.0001 < dt / 3; i++)
            gyro->Update(0.0001);

        for (auto plot : plots)
            plot->Update();

        traj->Draw(gyro->GetDiskPos() * 1.2);
    }

    if (isTimerEnabled)
    {
        time = time.addMSecs(static_cast<int>(dt * 1000));
        ui->timerL->setText("Время:  " + time.toString("mm:ss:zzz"));
    }

    elapsedTimer->restart();      
}

void MainWindow::DeletePlot(Plot *plot)
{
    auto iter = std::find(plots.begin(), plots.end(), plot);

    if (iter != plots.end())
        plots.erase(iter);
}

Qt3DCore::QEntity* MainWindow::addObject(QString obj, QString texture, QColor ambient, float scale)
{
    Qt3DCore::QEntity *entity = new Qt3DCore::QEntity(baseEntity);
    Qt3DRender::QMesh *mesh = new Qt3DRender::QMesh();
    mesh->setSource(QUrl::fromLocalFile(obj));

    Qt3DRender::QTextureLoader *texLoader = new Qt3DRender::QTextureLoader();
    texLoader->setSource(QUrl::fromLocalFile(texture));

    Qt3DExtras::QDiffuseSpecularMapMaterial *material = new Qt3DExtras::QDiffuseSpecularMapMaterial();
    material->setDiffuse(texLoader);
    material->setShininess(2.0f);
    material->setTextureScale(scale);
    material->setAmbient(ambient);
    material->setSpecular(texLoader);
    entity->addComponent(mesh);
    entity->addComponent(material);

    return entity;
}

void MainWindow::on_start_clicked()
{   
    isGyroEnabled = true;
    LockButtons(false, true, true);
    LockSlider(false);
}

void MainWindow::on_pause_clicked()
{
    isGyroEnabled = false;
    LockButtons(true, false, true);
    LockSlider(true);
}

void MainWindow::on_stop_clicked()
{

    isGyroEnabled = false;

    LockButtons(true, false, false);
    LockSlider(true);
    gyro->Init();

    ui->massS->setValue(gyro->GetMass() * 10);
    ui->radiusS->setValue(gyro->GetRadius() * 100);
    ui->lengthS->setValue(gyro->GetLength() * 100);
    ui->phi_dotS->setValue(gyro->GetPhiDot());
    ui->psi_dotS->setValue(gyro->GetPsi());
    ui->thetaS->setValue(gyro->GetTheta() * 1000);

    ui->massL->setText(QString("Масса диска: %1 кг").arg(gyro->GetMass()));
    ui->radiusL->setText(QString("Радиус диска: %1 м").arg(gyro->GetRadius()));
    ui->lengthL->setText(QString("Расстояние от диска до стержня: %1 м").arg(gyro->GetLength()));
    ui->phi_dotL->setText(QString("Начальная скорость прецессии: %1 рад/c").arg(gyro->GetPhiDot()));
    ui->psi_dotL->setText(QString("Скорость вращения диска: %1 рад/c").arg(gyro->GetPsiDot()));
    ui->thetaL->setText(QString("Наклон относительно вертикальной оси: %1 град").arg(round(gyro->GetTheta() / DegToRad)));

    for (auto plot : plots)
        plot->Restart();

    traj->Clear(gyro->GetDiskPos() * 1.2);
}

void MainWindow::on_lengthS_valueChanged(int value)
{
    gyro->SetLength(value * 0.01);
    ui->lengthL->setText(QString("Расстояние от диска до стержня: %1 м").arg(gyro->GetLength()));
}

void MainWindow::on_massS_valueChanged(int value)
{
    gyro->SetMass(value * 0.1);
    ui->massL->setText(QString("Масса диска: %1 кг").arg(gyro->GetMass()));
}

void MainWindow::on_radiusS_valueChanged(int value)
{
    gyro->SetRadius(value * 0.01);
    ui->radiusL->setText(QString("Радиус диска: %1 м").arg(gyro->GetRadius()));
}

void MainWindow::on_psi_dotS_valueChanged(int value)
{
    gyro->SetPsiDot(value);
    ui->psi_dotL->setText(QString("Скорость вращения диска: %1 рад/c").arg(gyro->GetPsiDot()));
}

void MainWindow::on_phi_dotS_valueChanged(int value)
{
     gyro->SetPhiDot(value * 0.1);
     ui->phi_dotL->setText(QString("Начальная скорость прецессии: %1 рад/c").arg(gyro->GetPhiDot()));
}

void MainWindow::on_thetaS_valueChanged(int value)
{
    gyro->SetTheta(value * 0.001);
    ui->thetaL->setText(QString("Наклон относительно вертикальной оси: %1 град").arg(round(gyro->GetTheta() / DegToRad)));

}

void MainWindow::on_action_triggered()
{
    this->close();
}

void MainWindow::on_action_2_triggered()
{
    Plot *plot = new Plot([this]()->double{ return gyro->GetPhi(); },
                          [this]()->double{ return gyro->GetTheta(); },
                          "Угол прецессии, рад",
                          "Угол нутации, рад",
                           this);

    plot->setWindowTitle("График зависимости θ от φ");
    plot->show();
    plots.append(plot);
}

void MainWindow::on_action_3_triggered()
{
    Plot *plot = new Plot([this]()->double{ return gyro->GetTime(); },
                          [this]()->double{ return gyro->GetTheta(); },
                          "Время, с",
                          "Угол нутации, рад",
                           this);

    plot->setWindowTitle("График зависимости θ от времени");
    plot->show();
    plots.append(plot);
}

void MainWindow::on_action_5_triggered()
{
    Plot *plot = new Plot([this]()->double{ return gyro->GetTime(); },
                          [this]()->double{ return gyro->GetEk(); },
                          "Время, с",
                          "Кинетическая энергия, Дж",
                           this);

    plot->setWindowTitle("График кинетической энергии");
    plot->show();
    plots.append(plot);
}

void MainWindow::on_action_6_triggered()
{
    Plot *plot = new Plot([this]()->double{ return gyro->GetTime(); },
                          [this]()->double{ return gyro->GetU(); },
                          "Время, с",
                          "Потенциальная энергия, Дж",
                           this);

    plot->setWindowTitle("График потенциальной энергии");
    plot->show();
    plots.append(plot);
}

void MainWindow::on_action_7_triggered()
{
    Plot *plot = new Plot([this]()->double{ return gyro->GetTime(); },
                          [this]()->double{ return gyro->GetE(); },
                          "Время, с",
                          "Полная энергия, Дж",
                           this);

    plot->setWindowTitle("График полной энергии");
    plot->show();
    plots.append(plot);
}

void MainWindow::on_timerStart_clicked()
{
    LockTimerButtons(false, true, true);
    isTimerEnabled = true;
}

void MainWindow::on_timerPause_clicked()
{
    LockTimerButtons(true, false, true);
    isTimerEnabled = false;
}

void MainWindow::on_timerStop_clicked()
{
     LockTimerButtons(true, false, false);
     isTimerEnabled = false;

     time.setHMS(0, 0, 0);
     ui->timerL->setText("Время:  " + time.toString("mm:ss:zzz"));
}

void MainWindow::on_action_9_triggered()
{
    help *help = new class help();
    help->show();
}

void MainWindow::on_action_8_triggered()
{
    Manual *manual = new Manual();
    manual->show();
}

void MainWindow::on_action_10_triggered()
{
    about *about = new class about();
    about->show();

}
