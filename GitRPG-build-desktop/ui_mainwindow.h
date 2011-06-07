/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created: Tue 7. Jun 20:02:26 2011
**      by: Qt User Interface Compiler version 4.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QGridLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QMainWindow>
#include <QtGui/QProgressBar>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QGridLayout *gridLayout_2;
    QGridLayout *gridLayout;
    QLabel *userName;
    QHBoxLayout *horizontalLayout;
    QLabel *jointLvl;
    QLabel *jointExp;
    QHBoxLayout *horizontalLayout_2;
    QLabel *plusLvl;
    QLabel *plusExp;
    QHBoxLayout *horizontalLayout_3;
    QLabel *minusLvl;
    QLabel *minusExp;
    QProgressBar *minusBar;
    QProgressBar *plusBar;
    QProgressBar *jointBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(368, 203);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        QIcon icon;
        icon.addFile(QString::fromUtf8("../images/tray.png"), QSize(), QIcon::Normal, QIcon::Off);
        MainWindow->setWindowIcon(icon);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        gridLayout_2 = new QGridLayout(centralWidget);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        gridLayout = new QGridLayout();
        gridLayout->setSpacing(6);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        userName = new QLabel(centralWidget);
        userName->setObjectName(QString::fromUtf8("userName"));
        QFont font;
        font.setFamily(QString::fromUtf8("Cooper Std Black"));
        font.setPointSize(11);
        font.setBold(true);
        font.setWeight(75);
        userName->setFont(font);
        userName->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(userName, 0, 0, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        jointLvl = new QLabel(centralWidget);
        jointLvl->setObjectName(QString::fromUtf8("jointLvl"));
        jointLvl->setFont(font);
        jointLvl->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        horizontalLayout->addWidget(jointLvl);

        jointExp = new QLabel(centralWidget);
        jointExp->setObjectName(QString::fromUtf8("jointExp"));
        jointExp->setFont(font);
        jointExp->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout->addWidget(jointExp);


        gridLayout->addLayout(horizontalLayout, 1, 0, 1, 1);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        plusLvl = new QLabel(centralWidget);
        plusLvl->setObjectName(QString::fromUtf8("plusLvl"));
        plusLvl->setFont(font);

        horizontalLayout_2->addWidget(plusLvl);

        plusExp = new QLabel(centralWidget);
        plusExp->setObjectName(QString::fromUtf8("plusExp"));
        plusExp->setFont(font);
        plusExp->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_2->addWidget(plusExp);


        gridLayout->addLayout(horizontalLayout_2, 3, 0, 1, 1);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        minusLvl = new QLabel(centralWidget);
        minusLvl->setObjectName(QString::fromUtf8("minusLvl"));
        minusLvl->setFont(font);

        horizontalLayout_3->addWidget(minusLvl);

        minusExp = new QLabel(centralWidget);
        minusExp->setObjectName(QString::fromUtf8("minusExp"));
        minusExp->setFont(font);
        minusExp->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_3->addWidget(minusExp);


        gridLayout->addLayout(horizontalLayout_3, 6, 0, 1, 1);

        minusBar = new QProgressBar(centralWidget);
        minusBar->setObjectName(QString::fromUtf8("minusBar"));
        minusBar->setStyleSheet(QString::fromUtf8("  QProgressBar {color:black; border: 0.5px solid grey; border-radius: 5px;} QProgressBar::chunk {background-color: #FF2929;}  "));
        minusBar->setMaximum(120);
        minusBar->setValue(12);
        minusBar->setAlignment(Qt::AlignCenter);
        minusBar->setTextVisible(true);
        minusBar->setOrientation(Qt::Horizontal);

        gridLayout->addWidget(minusBar, 7, 0, 1, 1);

        plusBar = new QProgressBar(centralWidget);
        plusBar->setObjectName(QString::fromUtf8("plusBar"));
        plusBar->setStyleSheet(QString::fromUtf8("  QProgressBar {color:black; border: 0.5px solid grey; border-radius: 5px;} QProgressBar::chunk {background-color: #44E823;}  "));
        plusBar->setMaximum(720);
        plusBar->setValue(250);
        plusBar->setAlignment(Qt::AlignCenter);
        plusBar->setTextVisible(true);
        plusBar->setOrientation(Qt::Horizontal);

        gridLayout->addWidget(plusBar, 5, 0, 1, 1);

        jointBar = new QProgressBar(centralWidget);
        jointBar->setObjectName(QString::fromUtf8("jointBar"));
        jointBar->setStyleSheet(QString::fromUtf8("  QProgressBar {color:black; border: 0.5px solid grey; border-radius: 5px;} QProgressBar::chunk {background-color: #3399FF;}  "));
        jointBar->setMaximum(1000);
        jointBar->setValue(755);
        jointBar->setAlignment(Qt::AlignCenter);
        jointBar->setTextVisible(true);
        jointBar->setOrientation(Qt::Horizontal);

        gridLayout->addWidget(jointBar, 2, 0, 1, 1);


        gridLayout_2->addLayout(gridLayout, 1, 0, 1, 1);

        MainWindow->setCentralWidget(centralWidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QString());
        userName->setText(QApplication::translate("MainWindow", "STALS", 0, QApplication::UnicodeUTF8));
        jointLvl->setText(QApplication::translate("MainWindow", "Joint Level 4", 0, QApplication::UnicodeUTF8));
        jointExp->setText(QApplication::translate("MainWindow", "[755 / 1000]", 0, QApplication::UnicodeUTF8));
        plusLvl->setText(QApplication::translate("MainWindow", "Insertions (+) Level 5", 0, QApplication::UnicodeUTF8));
        plusExp->setText(QApplication::translate("MainWindow", "[250 / 720 ]", 0, QApplication::UnicodeUTF8));
        minusLvl->setText(QApplication::translate("MainWindow", "Deleitions  (-)  Level 2", 0, QApplication::UnicodeUTF8));
        minusExp->setText(QApplication::translate("MainWindow", "[12 / 120]", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
