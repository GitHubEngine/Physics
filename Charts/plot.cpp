#include "plot.h"
#include "ui_plot.h"
#include "mainwindow.h"

Plot::Plot(std::function<double()> getarg, std::function<double()> getvalue, QString xLabel, QString yLabel, MainWindow *parent, QWidget *p) :
    QMainWindow(p),
    ui(new Ui::Plot),
    parent(parent),
    getarg(getarg),
    getvalue(getvalue)
{
    ui->setupUi(this);
    plot = ui->PlotSurface;

    plot->addGraph();
    plot->yAxis->setRange(getvalue() - 2, getvalue() + 2);
    plot->xAxis->setRange(getarg() - 2, getarg() + 2);

    plot->xAxis->setLabel(xLabel);
    plot->yAxis->setLabel(yLabel);

    plot->setInteractions(QCP::iRangeZoom | QCP::iRangeDrag);
    plot->setAttribute(Qt::WidgetAttribute::WA_DeleteOnClose);
}

void Plot::resizeEvent(QResizeEvent *re)
{
    ui->PlotSurface->setGeometry(0, 0, re->size().width(), re->size().height());
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

    args.append(arg);
    values.append(value);

    if (args.size() >= 500)
    {
        args.removeAt(0);
        values.removeAt(0);
    }

    QVector<double> vArgs = args.toVector();
    QVector<double> vValues = values.toVector();
    Draw(vArgs, vValues);
}

void Plot::Draw(QVector<double> &args, QVector<double> &values)
{
    plot->graph(0)->setData(args, values, true);
    plot->replot();
}

void Plot::Restart()
{
    args.clear();
    values.clear();
    plot->graph(0)->setData(args.toVector(), values.toVector(), true);
    plot->replot();
}
