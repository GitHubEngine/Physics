#ifndef PLOT4_H
#define PLOT4_H

#include <QMainWindow>
#include <qcustomplot.h>

namespace Ui {
class Plot4;
}

class Plot4 : public QMainWindow
{
    Q_OBJECT

public:

    explicit Plot4(std::function<double()> getarg, std::function<double()> getvalue,
                  QString args, QString values,
                  double args_start, double args_end,
                  double values_start, double values_end, QWidget *parent = nullptr);

    void Update();
    void BuildMySpecificPlot();
    void isFixed(bool fixed);

private:
    Ui::Plot4 *ui;

    std::function<double()> getarg;
    std::function<double()> getvalue;
    void Draw();

    QCustomPlot *plot4;
    double args_start, args_end, values_start, values_end;
    QCustomPlot *plot;
    QList<double> args;
    QList<double> values;
    bool _isFixed = true;
};

#endif
