#ifndef SPLASH_H
#define SPLASH_H

#include <QWidget>

namespace Ui {
class splash;
}

class splash : public QWidget
{
    Q_OBJECT

public:
    explicit splash(class MainWindow *pWindow, QWidget *parent = nullptr);
    ~splash();

private slots:
    void exit();
    void mousePressEvent(QMouseEvent *) override;

private:
    Ui::splash *ui;

    bool isClosed = false;
    class MainWindow *p;
    QTimer *timer;
};

#endif
