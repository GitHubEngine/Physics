/********************************************************************************
** Form generated from reading UI file 'splash.ui'
**
** Created by: Qt User Interface Compiler version 5.12.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SPLASH_H
#define UI_SPLASH_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_splash
{
public:
    QHBoxLayout *horizontalLayout;
    QLabel *label;

    void setupUi(QWidget *splash)
    {
        if (splash->objectName().isEmpty())
            splash->setObjectName(QString::fromUtf8("splash"));
        splash->resize(800, 800);
        splash->setMinimumSize(QSize(800, 800));
        splash->setMaximumSize(QSize(800, 800));
        horizontalLayout = new QHBoxLayout(splash);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(splash);
        label->setObjectName(QString::fromUtf8("label"));
        label->setMinimumSize(QSize(800, 800));
        label->setMaximumSize(QSize(800, 800));
        label->setPixmap(QPixmap(QString::fromUtf8(":/Res/Logos/splash.jpg")));
        label->setAlignment(Qt::AlignCenter);

        horizontalLayout->addWidget(label);


        retranslateUi(splash);

        QMetaObject::connectSlotsByName(splash);
    } // setupUi

    void retranslateUi(QWidget *splash)
    {
        splash->setWindowTitle(QApplication::translate("splash", "Form", nullptr));
        label->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class splash: public Ui_splash {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SPLASH_H
