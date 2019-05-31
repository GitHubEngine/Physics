#include "plot4.h"
#include "ui_plot4.h"
#include "mainwindow.h"

Plot4::Plot4(std::function<double()> getarg, std::function<double()> getvalue,
           QString args, QString values,
           double args_start, double args_end,
           double values_start, double values_end, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Plot4),
    getarg(getarg),
    getvalue(getvalue),
    args_start(args_start),
    args_end(args_end),
    values_start(values_start),
    values_end(values_end)
{
    ui->setupUi(this);

    plot4 = ui->PlotSurface;

    plot4->xAxis->setLabel(args);
    plot4->yAxis->setLabel(values);

    plot4->addGraph();
    plot4->xAxis->setRange(double(args_start), double(args_end));
    plot4->yAxis->setRange(double(values_start), double(values_end));

    plot4->setInteractions(QCP::iRangeDrag|QCP::iRangeZoom);
}

void Plot4::Update()
{
    args.append(getarg());
    values.append(getvalue());
    if (args.size() >= 250000)
    {
        args.removeAt(0);
        values.removeAt(0);
    }
    Draw();
}

void Plot4::BuildMySpecificPlot()
{
    args.clear();
    values.clear();
    args.append(1./sqrt(20e-3));
    args.append(1./sqrt(5e-3));
    values.append(getvalue() / sqrt(20e-3));
    values.append(getvalue() / sqrt(5e-3));
    Draw();
}

void Plot4::isFixed(bool fixed)
{
    _isFixed = fixed;
}

void Plot4::Draw()
{
    plot4->graph(0)->setData(args.toVector(), values.toVector(), true);
    double d = (args_end - args_start) / 10.;
    if (!_isFixed && args.last() > args_end - d)
        plot4->xAxis->setRange(args.last() - args_start + d, args.last() + d);
    plot4->replot();
}
