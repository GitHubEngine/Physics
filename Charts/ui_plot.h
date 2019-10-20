/********************************************************************************
** Form generated from reading UI file 'plot.ui'
**
** Created by: Qt User Interface Compiler version 5.12.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PLOT_H
#define UI_PLOT_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QWidget>
#include "qcustomplot.h"

QT_BEGIN_NAMESPACE

class Ui_Plot
{
public:
    QWidget *centralwidget;
    QCustomPlot *PlotSurface;
    QWidget *widget;

    void setupUi(QMainWindow *Plot)
    {
        if (Plot->objectName().isEmpty())
            Plot->setObjectName(QString::fromUtf8("Plot"));
        Plot->resize(800, 600);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Res/Logos/icon.ico"), QSize(), QIcon::Normal, QIcon::Off);
        Plot->setWindowIcon(icon);
        centralwidget = new QWidget(Plot);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        PlotSurface = new QCustomPlot(centralwidget);
        PlotSurface->setObjectName(QString::fromUtf8("PlotSurface"));
        PlotSurface->setGeometry(QRect(0, 0, 800, 450));
        widget = new QWidget(centralwidget);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(630, 370, 120, 80));
        Plot->setCentralWidget(centralwidget);

        retranslateUi(Plot);

        QMetaObject::connectSlotsByName(Plot);
    } // setupUi

    void retranslateUi(QMainWindow *Plot)
    {
        Plot->setWindowTitle(QApplication::translate("Plot", "\320\223\321\200\320\260\321\204\320\270\320\272", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Plot: public Ui_Plot {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PLOT_H
