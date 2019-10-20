#include "splash.h"
#include "ui_splash.h"
#include "mainwindow.h"
#include <QTimer>

splash::splash(MainWindow *pWindow, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::splash),
    p(pWindow)
{
    ui->setupUi(this);

    timer = new QTimer();
    timer->setInterval(5000);
    connect(timer, SIGNAL(timeout()), this, SLOT(exit()));
    timer->start();
}

splash::~splash()
{
    delete ui;
}

void splash::exit()
{
    timer->stop();
    this->close();

    if (!isClosed)
        p->show();
}

void splash::mousePressEvent(QMouseEvent *me)
{
    isClosed = true;
    p->show();
}

