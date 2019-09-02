#include "mainwindow.h"
#include "splash.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowState(Qt::WindowMaximized);

    splash s(&w);
    s.setWindowFlag(Qt::WindowType::SplashScreen);
    s.show();

    return a.exec();
}
