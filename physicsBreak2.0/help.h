#ifndef HELP_H
#define HELP_H

#include <QWidget>
#include <QScrollArea>
#include <QVBoxLayout>
#include <QLabel>
#include <QImage>
#include <Qt3DCore>
#include <QSpacerItem>



namespace Ui {
class help;
}

class help : public QWidget
{
    Q_OBJECT

public:
    explicit help(QWidget *parent = nullptr);
    void updspr(int);
    void keyPr(QKeyEvent *);



    ~help();

private slots:
    void on_pushButton_clicked();

private:
    Ui::help *ui;
};

QVBoxLayout *sRect();
QVBoxLayout *sRect3();



#endif // HELP_H
