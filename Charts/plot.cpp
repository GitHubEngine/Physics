#include "plot.h"
#include "ui_plot.h"
#include "mainwindow.h"

Plot::Plot(std::function<double()> getarg, std::function<double()> getvalue, MainWindow *parent, QWidget *p) :
    QMainWindow(p),
    ui(new Ui::Plot),
    parent(parent),
    getarg(getarg),
    getvalue(getvalue)
{
    ui->setupUi(this);
    plot = ui->PlotSurface;

    plot->addGraph();
    plot->yAxis->setRange(0, 3);

    minValue = maxValue = getvalue();
}

void Plot::resizeEvent(QResizeEvent *re)
{
    ui->PlotSurface->setGeometry(0, 0, re->size().width(), re->size().height() * 0.75);
}

void Plot::closeEvent(QCloseEvent *ce)
{
    delete plot;
    delete ui;
    parent->DeletePlot(this);
    this->destroy();
}

void Plot::Update()
{
    double arg = getarg();
    double value = getvalue();

    if (value > maxValue)
        maxValue = value;

    if (value < minValue)
        minValue = value;

    args.append(arg);
    values.append(value);

    if (args.size() >= 2500)
    {
        args.removeAt(0);
        values.removeAt(0);
    }

    Draw(args.toVector(), values.toVector());
}

void Plot::Draw(QVector<double> args, QVector<double> values)
{
    plot->graph(0)->setData(args, values, true);
    plot->xAxis->setRange(args.last() - 5, args.last() + 2);
    plot->yAxis->setRange(minValue * 0.9, maxValue * 1.1);
    plot->replot();
}

void Plot::Restart()
{
    args.clear();
    values.clear();
    plot->xAxis->setRange(-18, 2);
    plot->replot();
}
