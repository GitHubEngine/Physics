/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *action;
    QAction *action_2;
    QAction *action_3;
    QAction *action_5;
    QAction *action_6;
    QAction *action_7;
    QAction *action_8;
    QAction *action_9;
    QAction *action_10;
    QWidget *centralWidget;
    QWidget *horizontal;
    QHBoxLayout *horizontalLayout_11;
    QWidget *scene;
    QWidget *interface_2;
    QVBoxLayout *verticalLayout_5;
    QWidget *buttons;
    QHBoxLayout *horizontalLayout_12;
    QPushButton *start;
    QPushButton *pause;
    QPushButton *stop;
    QWidget *grid;
    QGridLayout *gridLayout_3;
    QSpacerItem *verticalSpacer_8;
    QSpacerItem *verticalSpacer_5;
    QLabel *lengthL;
    QLabel *psi_dotL;
    QSpacerItem *verticalSpacer_7;
    QSlider *psi_dotS;
    QSlider *radiusS;
    QSlider *phi_dotS;
    QSpacerItem *verticalSpacer_9;
    QLabel *radiusL;
    QLabel *massL;
    QSlider *thetaS;
    QSlider *massS;
    QSpacerItem *verticalSpacer_6;
    QLabel *thetaL;
    QLabel *phi_dotL;
    QSlider *lengthS;
    QSpacerItem *verticalSpacer;
    QFrame *line;
    QWidget *timer_2;
    QVBoxLayout *verticalLayout;
    QWidget *horizontalWidget;
    QHBoxLayout *horizontalLayout;
    QLabel *timerL;
    QWidget *horizontalWidget_4;
    QHBoxLayout *horizontalLayout_13;
    QPushButton *timerStart;
    QPushButton *timerPause;
    QPushButton *timerStop;
    QFrame *line_2;
    QSpacerItem *verticalSpacer_2;
    QLabel *label;
    QSpacerItem *verticalSpacer_3;
    QMenuBar *menuBar;
    QMenu *menu;
    QMenu *menu_2;
    QMenu *menu_4;
    QMenu *menu_3;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->setEnabled(true);
        MainWindow->resize(1200, 800);
        MainWindow->setMinimumSize(QSize(1200, 800));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Res/Logos/icon.ico"), QSize(), QIcon::Normal, QIcon::Off);
        MainWindow->setWindowIcon(icon);
        action = new QAction(MainWindow);
        action->setObjectName(QString::fromUtf8("action"));
        QFont font;
        font.setFamily(QString::fromUtf8("Calibri"));
        font.setPointSize(13);
        action->setFont(font);
        action_2 = new QAction(MainWindow);
        action_2->setObjectName(QString::fromUtf8("action_2"));
        action_2->setFont(font);
        action_3 = new QAction(MainWindow);
        action_3->setObjectName(QString::fromUtf8("action_3"));
        action_3->setFont(font);
        action_5 = new QAction(MainWindow);
        action_5->setObjectName(QString::fromUtf8("action_5"));
        action_5->setFont(font);
        action_6 = new QAction(MainWindow);
        action_6->setObjectName(QString::fromUtf8("action_6"));
        action_6->setFont(font);
        action_7 = new QAction(MainWindow);
        action_7->setObjectName(QString::fromUtf8("action_7"));
        action_7->setFont(font);
        action_8 = new QAction(MainWindow);
        action_8->setObjectName(QString::fromUtf8("action_8"));
        action_8->setFont(font);
        action_9 = new QAction(MainWindow);
        action_9->setObjectName(QString::fromUtf8("action_9"));
        action_9->setFont(font);
        action_10 = new QAction(MainWindow);
        action_10->setObjectName(QString::fromUtf8("action_10"));
        action_10->setFont(font);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        horizontal = new QWidget(centralWidget);
        horizontal->setObjectName(QString::fromUtf8("horizontal"));
        horizontal->setEnabled(true);
        horizontal->setGeometry(QRect(0, 0, 1200, 800));
        QSizePolicy sizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(horizontal->sizePolicy().hasHeightForWidth());
        horizontal->setSizePolicy(sizePolicy);
        horizontal->setMinimumSize(QSize(0, 0));
        horizontalLayout_11 = new QHBoxLayout(horizontal);
        horizontalLayout_11->setSpacing(6);
        horizontalLayout_11->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_11->setObjectName(QString::fromUtf8("horizontalLayout_11"));
        horizontalLayout_11->setContentsMargins(0, 0, 0, 0);
        scene = new QWidget(horizontal);
        scene->setObjectName(QString::fromUtf8("scene"));
        scene->setEnabled(false);
        scene->setMinimumSize(QSize(840, 800));

        horizontalLayout_11->addWidget(scene);

        interface_2 = new QWidget(horizontal);
        interface_2->setObjectName(QString::fromUtf8("interface_2"));
        interface_2->setEnabled(true);
        interface_2->setMinimumSize(QSize(460, 0));
        interface_2->setMaximumSize(QSize(460, 1600000));
        verticalLayout_5 = new QVBoxLayout(interface_2);
        verticalLayout_5->setSpacing(6);
        verticalLayout_5->setContentsMargins(11, 11, 11, 11);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        verticalLayout_5->setContentsMargins(0, 4, 5, 4);
        buttons = new QWidget(interface_2);
        buttons->setObjectName(QString::fromUtf8("buttons"));
        buttons->setEnabled(true);
        buttons->setMaximumSize(QSize(16777215, 1600000));
        horizontalLayout_12 = new QHBoxLayout(buttons);
        horizontalLayout_12->setSpacing(6);
        horizontalLayout_12->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_12->setObjectName(QString::fromUtf8("horizontalLayout_12"));
        start = new QPushButton(buttons);
        start->setObjectName(QString::fromUtf8("start"));
        start->setEnabled(true);
        start->setMinimumSize(QSize(80, 43));
        QFont font1;
        font1.setFamily(QString::fromUtf8("Calibri"));
        font1.setPointSize(17);
        start->setFont(font1);

        horizontalLayout_12->addWidget(start);

        pause = new QPushButton(buttons);
        pause->setObjectName(QString::fromUtf8("pause"));
        pause->setMinimumSize(QSize(80, 43));
        pause->setFont(font1);

        horizontalLayout_12->addWidget(pause);

        stop = new QPushButton(buttons);
        stop->setObjectName(QString::fromUtf8("stop"));
        stop->setEnabled(true);
        stop->setMinimumSize(QSize(80, 43));
        stop->setFont(font1);

        horizontalLayout_12->addWidget(stop);


        verticalLayout_5->addWidget(buttons);

        grid = new QWidget(interface_2);
        grid->setObjectName(QString::fromUtf8("grid"));
        gridLayout_3 = new QGridLayout(grid);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        verticalSpacer_8 = new QSpacerItem(20, 5, QSizePolicy::Minimum, QSizePolicy::Fixed);

        gridLayout_3->addItem(verticalSpacer_8, 18, 0, 1, 1);

        verticalSpacer_5 = new QSpacerItem(20, 5, QSizePolicy::Minimum, QSizePolicy::Fixed);

        gridLayout_3->addItem(verticalSpacer_5, 6, 0, 1, 1);

        lengthL = new QLabel(grid);
        lengthL->setObjectName(QString::fromUtf8("lengthL"));
        lengthL->setEnabled(true);
        QFont font2;
        font2.setFamily(QString::fromUtf8("Calibri"));
        font2.setPointSize(16);
        lengthL->setFont(font2);

        gridLayout_3->addWidget(lengthL, 0, 0, 1, 1);

        psi_dotL = new QLabel(grid);
        psi_dotL->setObjectName(QString::fromUtf8("psi_dotL"));
        psi_dotL->setEnabled(true);
        psi_dotL->setFont(font2);

        gridLayout_3->addWidget(psi_dotL, 15, 0, 1, 1);

        verticalSpacer_7 = new QSpacerItem(20, 5, QSizePolicy::Minimum, QSizePolicy::Fixed);

        gridLayout_3->addItem(verticalSpacer_7, 14, 0, 1, 1);

        psi_dotS = new QSlider(grid);
        psi_dotS->setObjectName(QString::fromUtf8("psi_dotS"));
        psi_dotS->setEnabled(true);
        psi_dotS->setMinimum(500);
        psi_dotS->setMaximum(1000);
        psi_dotS->setOrientation(Qt::Horizontal);

        gridLayout_3->addWidget(psi_dotS, 16, 0, 1, 1);

        radiusS = new QSlider(grid);
        radiusS->setObjectName(QString::fromUtf8("radiusS"));
        radiusS->setEnabled(true);
        radiusS->setMinimum(5);
        radiusS->setMaximum(8);
        radiusS->setValue(8);
        radiusS->setOrientation(Qt::Horizontal);

        gridLayout_3->addWidget(radiusS, 12, 0, 1, 1);

        phi_dotS = new QSlider(grid);
        phi_dotS->setObjectName(QString::fromUtf8("phi_dotS"));
        phi_dotS->setEnabled(true);
        phi_dotS->setMinimum(-30);
        phi_dotS->setMaximum(30);
        phi_dotS->setOrientation(Qt::Horizontal);

        gridLayout_3->addWidget(phi_dotS, 20, 0, 1, 1);

        verticalSpacer_9 = new QSpacerItem(20, 5, QSizePolicy::Minimum, QSizePolicy::Fixed);

        gridLayout_3->addItem(verticalSpacer_9, 22, 0, 1, 1);

        radiusL = new QLabel(grid);
        radiusL->setObjectName(QString::fromUtf8("radiusL"));
        radiusL->setEnabled(true);
        radiusL->setFont(font2);

        gridLayout_3->addWidget(radiusL, 11, 0, 1, 1);

        massL = new QLabel(grid);
        massL->setObjectName(QString::fromUtf8("massL"));
        massL->setEnabled(true);
        massL->setFont(font2);

        gridLayout_3->addWidget(massL, 7, 0, 1, 1);

        thetaS = new QSlider(grid);
        thetaS->setObjectName(QString::fromUtf8("thetaS"));
        thetaS->setEnabled(true);
        thetaS->setMinimum(785);
        thetaS->setMaximum(1570);
        thetaS->setValue(1570);
        thetaS->setOrientation(Qt::Horizontal);

        gridLayout_3->addWidget(thetaS, 24, 0, 1, 1);

        massS = new QSlider(grid);
        massS->setObjectName(QString::fromUtf8("massS"));
        massS->setEnabled(true);
        massS->setMinimum(1);
        massS->setMaximum(20);
        massS->setOrientation(Qt::Horizontal);

        gridLayout_3->addWidget(massS, 8, 0, 1, 1);

        verticalSpacer_6 = new QSpacerItem(20, 5, QSizePolicy::Minimum, QSizePolicy::Fixed);

        gridLayout_3->addItem(verticalSpacer_6, 10, 0, 1, 1);

        thetaL = new QLabel(grid);
        thetaL->setObjectName(QString::fromUtf8("thetaL"));
        thetaL->setEnabled(true);
        thetaL->setFont(font2);
        thetaL->setScaledContents(false);
        thetaL->setWordWrap(true);

        gridLayout_3->addWidget(thetaL, 23, 0, 1, 1);

        phi_dotL = new QLabel(grid);
        phi_dotL->setObjectName(QString::fromUtf8("phi_dotL"));
        phi_dotL->setEnabled(true);
        phi_dotL->setFont(font2);

        gridLayout_3->addWidget(phi_dotL, 19, 0, 1, 1);

        lengthS = new QSlider(grid);
        lengthS->setObjectName(QString::fromUtf8("lengthS"));
        lengthS->setEnabled(true);
        lengthS->setMinimum(15);
        lengthS->setMaximum(20);
        lengthS->setValue(20);
        lengthS->setOrientation(Qt::Horizontal);

        gridLayout_3->addWidget(lengthS, 1, 0, 1, 1);


        verticalLayout_5->addWidget(grid);

        verticalSpacer = new QSpacerItem(20, 107, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_5->addItem(verticalSpacer);

        line = new QFrame(interface_2);
        line->setObjectName(QString::fromUtf8("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        verticalLayout_5->addWidget(line);

        timer_2 = new QWidget(interface_2);
        timer_2->setObjectName(QString::fromUtf8("timer_2"));
        timer_2->setMinimumSize(QSize(0, 0));
        verticalLayout = new QVBoxLayout(timer_2);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalWidget = new QWidget(timer_2);
        horizontalWidget->setObjectName(QString::fromUtf8("horizontalWidget"));
        horizontalWidget->setMinimumSize(QSize(0, 0));
        horizontalLayout = new QHBoxLayout(horizontalWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        timerL = new QLabel(horizontalWidget);
        timerL->setObjectName(QString::fromUtf8("timerL"));
        timerL->setMinimumSize(QSize(0, 30));
        timerL->setMaximumSize(QSize(16777215, 16000));
        QFont font3;
        font3.setFamily(QString::fromUtf8("Calibri"));
        font3.setPointSize(20);
        timerL->setFont(font3);
        timerL->setAlignment(Qt::AlignCenter);
        timerL->setMargin(0);

        horizontalLayout->addWidget(timerL);


        verticalLayout->addWidget(horizontalWidget);

        horizontalWidget_4 = new QWidget(timer_2);
        horizontalWidget_4->setObjectName(QString::fromUtf8("horizontalWidget_4"));
        horizontalWidget_4->setEnabled(true);
        horizontalWidget_4->setMaximumSize(QSize(16777215, 49));
        horizontalLayout_13 = new QHBoxLayout(horizontalWidget_4);
        horizontalLayout_13->setSpacing(6);
        horizontalLayout_13->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_13->setObjectName(QString::fromUtf8("horizontalLayout_13"));
        horizontalLayout_13->setContentsMargins(0, 0, 0, 0);
        timerStart = new QPushButton(horizontalWidget_4);
        timerStart->setObjectName(QString::fromUtf8("timerStart"));
        timerStart->setEnabled(true);
        timerStart->setMinimumSize(QSize(80, 43));
        timerStart->setFont(font1);

        horizontalLayout_13->addWidget(timerStart);

        timerPause = new QPushButton(horizontalWidget_4);
        timerPause->setObjectName(QString::fromUtf8("timerPause"));
        timerPause->setMinimumSize(QSize(80, 43));
        timerPause->setFont(font1);

        horizontalLayout_13->addWidget(timerPause);

        timerStop = new QPushButton(horizontalWidget_4);
        timerStop->setObjectName(QString::fromUtf8("timerStop"));
        timerStop->setEnabled(true);
        timerStop->setMinimumSize(QSize(80, 43));
        timerStop->setFont(font1);

        horizontalLayout_13->addWidget(timerStop);


        verticalLayout->addWidget(horizontalWidget_4);


        verticalLayout_5->addWidget(timer_2);

        line_2 = new QFrame(interface_2);
        line_2->setObjectName(QString::fromUtf8("line_2"));
        line_2->setFrameShape(QFrame::HLine);
        line_2->setFrameShadow(QFrame::Sunken);

        verticalLayout_5->addWidget(line_2);

        verticalSpacer_2 = new QSpacerItem(20, 400, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_5->addItem(verticalSpacer_2);

        label = new QLabel(interface_2);
        label->setObjectName(QString::fromUtf8("label"));
        label->setMinimumSize(QSize(300, 122));
        label->setPixmap(QPixmap(QString::fromUtf8(":/Res/Logos/NSTU.png")));
        label->setScaledContents(false);
        label->setAlignment(Qt::AlignCenter);

        verticalLayout_5->addWidget(label);

        verticalSpacer_3 = new QSpacerItem(20, 30, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_5->addItem(verticalSpacer_3);


        horizontalLayout_11->addWidget(interface_2);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setEnabled(true);
        menuBar->setGeometry(QRect(0, 0, 1200, 27));
        menuBar->setFont(font);
        menuBar->setDefaultUp(false);
        menu = new QMenu(menuBar);
        menu->setObjectName(QString::fromUtf8("menu"));
        menu->setFont(font);
        menu_2 = new QMenu(menuBar);
        menu_2->setObjectName(QString::fromUtf8("menu_2"));
        menu_2->setFont(font);
        menu_4 = new QMenu(menu_2);
        menu_4->setObjectName(QString::fromUtf8("menu_4"));
        menu_4->setFont(font);
        menu_3 = new QMenu(menuBar);
        menu_3->setObjectName(QString::fromUtf8("menu_3"));
        menu_3->setFont(font);
        MainWindow->setMenuBar(menuBar);

        menuBar->addAction(menu->menuAction());
        menuBar->addAction(menu_2->menuAction());
        menuBar->addAction(menu_3->menuAction());
        menu->addAction(action);
        menu_2->addAction(action_2);
        menu_2->addAction(action_3);
        menu_2->addAction(menu_4->menuAction());
        menu_4->addAction(action_5);
        menu_4->addAction(action_6);
        menu_4->addAction(action_7);
        menu_3->addAction(action_8);
        menu_3->addAction(action_9);
        menu_3->addAction(action_10);
        menu_3->addSeparator();

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "\320\237\321\200\320\265\321\206\320\265\321\201\321\201\320\270\321\217 \320\270 \320\275\321\203\321\202\320\260\321\206\320\270\321\217 \320\263\320\270\321\200\320\276\321\201\320\272\320\276\320\277\320\260", nullptr));
        action->setText(QApplication::translate("MainWindow", "\320\222\321\213\321\205\320\276\320\264", nullptr));
        action_2->setText(QApplication::translate("MainWindow", "\320\223\321\200\320\260\321\204\320\270\320\272 \320\267\320\260\320\262\320\270\321\201\320\270\320\274\320\276\321\201\321\202\320\270 \316\270 \320\276\321\202 \317\206", nullptr));
        action_3->setText(QApplication::translate("MainWindow", "\320\223\321\200\320\260\321\204\320\270\320\272 \320\267\320\260\320\262\320\270\321\201\320\270\320\274\320\276\321\201\321\202\320\270 \316\270 \320\276\321\202 \320\262\321\200\320\265\320\274\320\265\320\275\320\270", nullptr));
        action_5->setText(QApplication::translate("MainWindow", "\320\232\320\270\320\275\320\265\321\202\320\270\321\207\320\265\321\201\320\272\320\260\321\217 \321\215\320\275\320\265\321\200\320\263\320\270\321\217", nullptr));
        action_6->setText(QApplication::translate("MainWindow", "\320\237\320\276\321\202\320\265\320\275\321\206\320\270\320\260\320\273\321\214\320\275\320\260\321\217 \321\215\320\275\320\265\321\200\320\263\320\270\321\217", nullptr));
        action_7->setText(QApplication::translate("MainWindow", "\320\237\320\276\320\273\320\275\320\260\321\217 \321\215\320\275\320\265\321\200\320\263\320\270\321\217", nullptr));
        action_8->setText(QApplication::translate("MainWindow", "\320\240\321\203\320\272\320\276\320\262\320\276\320\264\321\201\321\202\320\262\320\276 \320\277\320\276\320\273\321\214\320\267\320\276\320\262\320\260\321\202\320\265\320\273\321\217", nullptr));
        action_9->setText(QApplication::translate("MainWindow", "\320\241\320\277\321\200\320\260\320\262\320\272\320\260", nullptr));
        action_10->setText(QApplication::translate("MainWindow", "\320\240\320\260\320\267\321\200\320\260\320\261\320\276\321\202\321\207\320\270\320\272\320\270", nullptr));
        start->setText(QApplication::translate("MainWindow", "\320\227\320\260\320\277\321\203\321\201\320\272", nullptr));
        pause->setText(QApplication::translate("MainWindow", "\320\237\320\260\321\203\320\267\320\260", nullptr));
        stop->setText(QApplication::translate("MainWindow", "\320\241\320\261\321\200\320\276\321\201", nullptr));
        lengthL->setText(QString());
        psi_dotL->setText(QString());
        radiusL->setText(QString());
        massL->setText(QString());
        thetaL->setText(QString());
        phi_dotL->setText(QString());
        timerL->setText(QString());
        timerStart->setText(QApplication::translate("MainWindow", "\320\227\320\260\320\277\321\203\321\201\320\272", nullptr));
        timerPause->setText(QApplication::translate("MainWindow", "\320\237\320\260\321\203\320\267\320\260", nullptr));
        timerStop->setText(QApplication::translate("MainWindow", "\320\241\320\261\321\200\320\276\321\201", nullptr));
        label->setText(QString());
        menu->setTitle(QApplication::translate("MainWindow", "\320\244\320\260\320\271\320\273", nullptr));
        menu_2->setTitle(QApplication::translate("MainWindow", "\320\223\321\200\320\260\321\204\320\270\320\272\320\270", nullptr));
        menu_4->setTitle(QApplication::translate("MainWindow", "\320\223\321\200\320\260\321\204\320\270\320\272\320\270 \321\215\320\275\320\265\321\200\320\263\320\270\320\270", nullptr));
        menu_3->setTitle(QApplication::translate("MainWindow", "\320\236 \320\277\321\200\320\276\320\263\321\200\320\260\320\274\320\274\320\265", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
