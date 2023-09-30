/********************************************************************************
** Form generated from reading UI file 'greenhouse.ui'
**
** Created by: Qt User Interface Compiler version 6.4.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GREENHOUSE_H
#define UI_GREENHOUSE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCalendarWidget>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_GreenHouseClass
{
public:
    QWidget *centralWidget;
    QGroupBox *netConfGroupBox;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout_2;
    QLabel *ipLabel;
    QLabel *portLabel;
    QLCDNumber *lcdNumber;
    QLineEdit *ipEdit;
    QFrame *line;
    QFrame *line_2;
    QGroupBox *groupBox;
    QPushButton *openHumAndTemBtn;
    QLabel *temLabel;
    QTextBrowser *humAndTemBrowser;
    QLabel *humLabel;
    QFrame *line_3;
    QCalendarWidget *calendarWidget;
    QFrame *line_4;
    QFrame *line_5;
    QGroupBox *groupBox_3;
    QLabel *humSoilLabel;
    QTextBrowser *humSoilBrowser;
    QPushButton *openHumSoilBtn;
    QWidget *layoutWidget1;
    QHBoxLayout *horizontalLayout;
    QWidget *layoutWidget2;
    QVBoxLayout *verticalLayout_3;
    QPushButton *openBtn;
    QPushButton *closeBtn;
    QGroupBox *groupBox_5;
    QTextBrowser *recBrowser;
    QPushButton *cleanRecBtn;
    QGroupBox *groupBox_6;
    QTextBrowser *lightBrowser;
    QLabel *lightLabel;
    QPushButton *openLightBtn;
    QFrame *line_6;
    QFrame *line_7;
    QGroupBox *groupBox_7;
    QPushButton *openHCSR04Btn;
    QTextEdit *HCSR04Edit;
    QLabel *HCSR04Label;
    QGroupBox *groupBox_8;
    QPushButton *openHCSR501Btn;
    QLabel *HCSR501Label;
    QTextBrowser *HCSR501Browser;
    QGroupBox *groupBox_9;
    QPushButton *level3Btn;
    QPushButton *fanBtn;
    QPushButton *level2Btn;
    QLineEdit *lineEdit;
    QPushButton *level1Btn;
    QGroupBox *groupBox_10;
    QLineEdit *sendEdit;
    QPushButton *sendBtn;
    QPushButton *cleanSendBtn;
    QWidget *widget;
    QPushButton *cleanAllBtn;
    QLineEdit *lineEdit_2;
    QFrame *line_8;
    QFrame *line_9;
    QFrame *line_10;
    QFrame *line_11;
    QFrame *line_12;
    QStatusBar *statusBar;
    QMenuBar *menuBar;

    void setupUi(QMainWindow *GreenHouseClass)
    {
        if (GreenHouseClass->objectName().isEmpty())
            GreenHouseClass->setObjectName("GreenHouseClass");
        GreenHouseClass->resize(1173, 835);
        GreenHouseClass->setTabletTracking(false);
        GreenHouseClass->setAcceptDrops(false);
        GreenHouseClass->setStyleSheet(QString::fromUtf8(""));
        centralWidget = new QWidget(GreenHouseClass);
        centralWidget->setObjectName("centralWidget");
        netConfGroupBox = new QGroupBox(centralWidget);
        netConfGroupBox->setObjectName("netConfGroupBox");
        netConfGroupBox->setGeometry(QRect(20, 60, 211, 151));
        layoutWidget = new QWidget(netConfGroupBox);
        layoutWidget->setObjectName("layoutWidget");
        layoutWidget->setGeometry(QRect(10, 20, 51, 121));
        verticalLayout_2 = new QVBoxLayout(layoutWidget);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        ipLabel = new QLabel(layoutWidget);
        ipLabel->setObjectName("ipLabel");
        ipLabel->setStyleSheet(QString::fromUtf8("border-image: url(:/img/ip.png)"));

        verticalLayout_2->addWidget(ipLabel);

        portLabel = new QLabel(layoutWidget);
        portLabel->setObjectName("portLabel");
        portLabel->setStyleSheet(QString::fromUtf8("border-image: url(:/img/duan.png);"));

        verticalLayout_2->addWidget(portLabel);

        lcdNumber = new QLCDNumber(netConfGroupBox);
        lcdNumber->setObjectName("lcdNumber");
        lcdNumber->setGeometry(QRect(70, 90, 121, 41));
        ipEdit = new QLineEdit(netConfGroupBox);
        ipEdit->setObjectName("ipEdit");
        ipEdit->setGeometry(QRect(70, 30, 121, 31));
        QFont font;
        font.setPointSize(9);
        ipEdit->setFont(font);
        ipEdit->setLayoutDirection(Qt::LeftToRight);
        ipEdit->setAlignment(Qt::AlignCenter);
        ipEdit->setReadOnly(true);
        line = new QFrame(centralWidget);
        line->setObjectName("line");
        line->setGeometry(QRect(10, 220, 251, 41));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);
        line_2 = new QFrame(centralWidget);
        line_2->setObjectName("line_2");
        line_2->setGeometry(QRect(250, 40, 31, 201));
        line_2->setFrameShape(QFrame::VLine);
        line_2->setFrameShadow(QFrame::Sunken);
        groupBox = new QGroupBox(centralWidget);
        groupBox->setObjectName("groupBox");
        groupBox->setGeometry(QRect(280, 40, 261, 241));
        openHumAndTemBtn = new QPushButton(groupBox);
        openHumAndTemBtn->setObjectName("openHumAndTemBtn");
        openHumAndTemBtn->setGeometry(QRect(140, 40, 111, 41));
        temLabel = new QLabel(groupBox);
        temLabel->setObjectName("temLabel");
        temLabel->setGeometry(QRect(10, 20, 61, 71));
        temLabel->setStyleSheet(QString::fromUtf8("image: url(:/img/temp.png);"));
        humAndTemBrowser = new QTextBrowser(groupBox);
        humAndTemBrowser->setObjectName("humAndTemBrowser");
        humAndTemBrowser->setGeometry(QRect(20, 90, 211, 131));
        humLabel = new QLabel(groupBox);
        humLabel->setObjectName("humLabel");
        humLabel->setGeometry(QRect(90, 20, 61, 61));
        humLabel->setStyleSheet(QString::fromUtf8("border-image: url(:/img/humi.png);"));
        line_3 = new QFrame(centralWidget);
        line_3->setObjectName("line_3");
        line_3->setGeometry(QRect(520, 50, 31, 191));
        line_3->setFrameShape(QFrame::VLine);
        line_3->setFrameShadow(QFrame::Sunken);
        calendarWidget = new QCalendarWidget(centralWidget);
        calendarWidget->setObjectName("calendarWidget");
        calendarWidget->setGeometry(QRect(830, 50, 248, 183));
        line_4 = new QFrame(centralWidget);
        line_4->setObjectName("line_4");
        line_4->setGeometry(QRect(250, 240, 31, 181));
        line_4->setFrameShape(QFrame::VLine);
        line_4->setFrameShadow(QFrame::Sunken);
        line_5 = new QFrame(centralWidget);
        line_5->setObjectName("line_5");
        line_5->setGeometry(QRect(520, 240, 31, 181));
        line_5->setFrameShape(QFrame::VLine);
        line_5->setFrameShadow(QFrame::Sunken);
        groupBox_3 = new QGroupBox(centralWidget);
        groupBox_3->setObjectName("groupBox_3");
        groupBox_3->setGeometry(QRect(10, 240, 251, 171));
        humSoilLabel = new QLabel(groupBox_3);
        humSoilLabel->setObjectName("humSoilLabel");
        humSoilLabel->setGeometry(QRect(20, 20, 71, 71));
        humSoilLabel->setStyleSheet(QString::fromUtf8("border-image: url(:/img/humi_soil.png);"));
        humSoilBrowser = new QTextBrowser(groupBox_3);
        humSoilBrowser->setObjectName("humSoilBrowser");
        humSoilBrowser->setGeometry(QRect(10, 90, 231, 71));
        openHumSoilBtn = new QPushButton(groupBox_3);
        openHumSoilBtn->setObjectName("openHumSoilBtn");
        openHumSoilBtn->setGeometry(QRect(100, 30, 131, 31));
        layoutWidget1 = new QWidget(centralWidget);
        layoutWidget1->setObjectName("layoutWidget1");
        layoutWidget1->setGeometry(QRect(0, 0, 2, 2));
        horizontalLayout = new QHBoxLayout(layoutWidget1);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        layoutWidget2 = new QWidget(centralWidget);
        layoutWidget2->setObjectName("layoutWidget2");
        layoutWidget2->setGeometry(QRect(0, 0, 2, 2));
        verticalLayout_3 = new QVBoxLayout(layoutWidget2);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName("verticalLayout_3");
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        openBtn = new QPushButton(centralWidget);
        openBtn->setObjectName("openBtn");
        openBtn->setEnabled(true);
        openBtn->setGeometry(QRect(10, 10, 41, 41));
        openBtn->setMouseTracking(false);
        openBtn->setTabletTracking(false);
        openBtn->setContextMenuPolicy(Qt::PreventContextMenu);
        openBtn->setAcceptDrops(false);
        openBtn->setAutoFillBackground(false);
        openBtn->setStyleSheet(QString::fromUtf8(""));
        openBtn->setCheckable(false);
        openBtn->setAutoRepeat(false);
        openBtn->setAutoExclusive(false);
        openBtn->setFlat(false);
        closeBtn = new QPushButton(centralWidget);
        closeBtn->setObjectName("closeBtn");
        closeBtn->setGeometry(QRect(60, 10, 41, 41));
        closeBtn->setAutoFillBackground(false);
        closeBtn->setStyleSheet(QString::fromUtf8(""));
        groupBox_5 = new QGroupBox(centralWidget);
        groupBox_5->setObjectName("groupBox_5");
        groupBox_5->setGeometry(QRect(0, 450, 521, 111));
        recBrowser = new QTextBrowser(groupBox_5);
        recBrowser->setObjectName("recBrowser");
        recBrowser->setGeometry(QRect(10, 20, 441, 71));
        cleanRecBtn = new QPushButton(groupBox_5);
        cleanRecBtn->setObjectName("cleanRecBtn");
        cleanRecBtn->setGeometry(QRect(460, 10, 41, 41));
        cleanRecBtn->setStyleSheet(QString::fromUtf8("border-image: url(:/img/clear_b.png);"));
        groupBox_6 = new QGroupBox(centralWidget);
        groupBox_6->setObjectName("groupBox_6");
        groupBox_6->setGeometry(QRect(540, 240, 261, 171));
        lightBrowser = new QTextBrowser(groupBox_6);
        lightBrowser->setObjectName("lightBrowser");
        lightBrowser->setGeometry(QRect(10, 100, 241, 61));
        lightLabel = new QLabel(groupBox_6);
        lightLabel->setObjectName("lightLabel");
        lightLabel->setGeometry(QRect(20, 30, 71, 71));
        lightLabel->setStyleSheet(QString::fromUtf8("border-image: url(:/img/light.png);"));
        openLightBtn = new QPushButton(groupBox_6);
        openLightBtn->setObjectName("openLightBtn");
        openLightBtn->setGeometry(QRect(120, 20, 111, 41));
        line_6 = new QFrame(centralWidget);
        line_6->setObjectName("line_6");
        line_6->setGeometry(QRect(520, 420, 31, 171));
        line_6->setFrameShape(QFrame::VLine);
        line_6->setFrameShadow(QFrame::Sunken);
        line_7 = new QFrame(centralWidget);
        line_7->setObjectName("line_7");
        line_7->setGeometry(QRect(0, 400, 1081, 41));
        line_7->setFrameShape(QFrame::HLine);
        line_7->setFrameShadow(QFrame::Sunken);
        groupBox_7 = new QGroupBox(centralWidget);
        groupBox_7->setObjectName("groupBox_7");
        groupBox_7->setGeometry(QRect(560, 50, 241, 171));
        openHCSR04Btn = new QPushButton(groupBox_7);
        openHCSR04Btn->setObjectName("openHCSR04Btn");
        openHCSR04Btn->setGeometry(QRect(70, 30, 121, 41));
        HCSR04Edit = new QTextEdit(groupBox_7);
        HCSR04Edit->setObjectName("HCSR04Edit");
        HCSR04Edit->setGeometry(QRect(20, 90, 201, 71));
        HCSR04Label = new QLabel(groupBox_7);
        HCSR04Label->setObjectName("HCSR04Label");
        HCSR04Label->setGeometry(QRect(10, 20, 61, 61));
        HCSR04Label->setStyleSheet(QString::fromUtf8("border-image: url(:/img/wifi_on.png);"));
        groupBox_8 = new QGroupBox(centralWidget);
        groupBox_8->setObjectName("groupBox_8");
        groupBox_8->setGeometry(QRect(830, 250, 241, 161));
        openHCSR501Btn = new QPushButton(groupBox_8);
        openHCSR501Btn->setObjectName("openHCSR501Btn");
        openHCSR501Btn->setGeometry(QRect(80, 30, 131, 41));
        HCSR501Label = new QLabel(groupBox_8);
        HCSR501Label->setObjectName("HCSR501Label");
        HCSR501Label->setGeometry(QRect(10, 20, 61, 61));
        HCSR501Label->setStyleSheet(QString::fromUtf8("border-image: url(:/img/client.png);"));
        HCSR501Browser = new QTextBrowser(groupBox_8);
        HCSR501Browser->setObjectName("HCSR501Browser");
        HCSR501Browser->setGeometry(QRect(10, 90, 221, 61));
        groupBox_9 = new QGroupBox(centralWidget);
        groupBox_9->setObjectName("groupBox_9");
        groupBox_9->setGeometry(QRect(600, 430, 151, 141));
        level3Btn = new QPushButton(groupBox_9);
        level3Btn->setObjectName("level3Btn");
        level3Btn->setGeometry(QRect(110, 100, 31, 31));
        level3Btn->setStyleSheet(QString::fromUtf8(""));
        fanBtn = new QPushButton(groupBox_9);
        fanBtn->setObjectName("fanBtn");
        fanBtn->setGeometry(QRect(20, 20, 51, 51));
        fanBtn->setStyleSheet(QString::fromUtf8("border-image: url(:/img/fan.png);"));
        level2Btn = new QPushButton(groupBox_9);
        level2Btn->setObjectName("level2Btn");
        level2Btn->setGeometry(QRect(110, 60, 31, 31));
        level2Btn->setStyleSheet(QString::fromUtf8(""));
        lineEdit = new QLineEdit(groupBox_9);
        lineEdit->setObjectName("lineEdit");
        lineEdit->setGeometry(QRect(10, 90, 71, 21));
        lineEdit->setAlignment(Qt::AlignCenter);
        level1Btn = new QPushButton(groupBox_9);
        level1Btn->setObjectName("level1Btn");
        level1Btn->setGeometry(QRect(110, 20, 31, 31));
        level1Btn->setStyleSheet(QString::fromUtf8(""));
        groupBox_10 = new QGroupBox(centralWidget);
        groupBox_10->setObjectName("groupBox_10");
        groupBox_10->setGeometry(QRect(280, 290, 241, 111));
        sendEdit = new QLineEdit(groupBox_10);
        sendEdit->setObjectName("sendEdit");
        sendEdit->setGeometry(QRect(10, 40, 181, 51));
        sendBtn = new QPushButton(groupBox_10);
        sendBtn->setObjectName("sendBtn");
        sendBtn->setGeometry(QRect(190, 10, 51, 51));
        sendBtn->setStyleSheet(QString::fromUtf8("border-image: url(:/img/send.png);"));
        cleanSendBtn = new QPushButton(groupBox_10);
        cleanSendBtn->setObjectName("cleanSendBtn");
        cleanSendBtn->setGeometry(QRect(190, 60, 51, 51));
        cleanSendBtn->setStyleSheet(QString::fromUtf8("border-image: url(:/img/clearS.png);"));
        widget = new QWidget(centralWidget);
        widget->setObjectName("widget");
        widget->setGeometry(QRect(820, 420, 171, 161));
        cleanAllBtn = new QPushButton(widget);
        cleanAllBtn->setObjectName("cleanAllBtn");
        cleanAllBtn->setGeometry(QRect(20, 0, 131, 131));
        cleanAllBtn->setStyleSheet(QString::fromUtf8("border-image: url(:/img/clear.png);"));
        lineEdit_2 = new QLineEdit(widget);
        lineEdit_2->setObjectName("lineEdit_2");
        lineEdit_2->setGeometry(QRect(10, 140, 161, 21));
        lineEdit_2->setAlignment(Qt::AlignCenter);
        line_8 = new QFrame(centralWidget);
        line_8->setObjectName("line_8");
        line_8->setGeometry(QRect(540, 220, 541, 41));
        line_8->setFrameShape(QFrame::HLine);
        line_8->setFrameShadow(QFrame::Sunken);
        line_9 = new QFrame(centralWidget);
        line_9->setObjectName("line_9");
        line_9->setGeometry(QRect(270, 260, 261, 41));
        line_9->setFrameShape(QFrame::HLine);
        line_9->setFrameShadow(QFrame::Sunken);
        line_10 = new QFrame(centralWidget);
        line_10->setObjectName("line_10");
        line_10->setGeometry(QRect(800, 50, 31, 371));
        line_10->setFrameShape(QFrame::VLine);
        line_10->setFrameShadow(QFrame::Sunken);
        line_11 = new QFrame(centralWidget);
        line_11->setObjectName("line_11");
        line_11->setGeometry(QRect(0, 570, 1081, 41));
        line_11->setFrameShape(QFrame::HLine);
        line_11->setFrameShadow(QFrame::Sunken);
        line_12 = new QFrame(centralWidget);
        line_12->setObjectName("line_12");
        line_12->setGeometry(QRect(800, 420, 31, 171));
        line_12->setFrameShape(QFrame::VLine);
        line_12->setFrameShadow(QFrame::Sunken);
        GreenHouseClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(GreenHouseClass);
        statusBar->setObjectName("statusBar");
        GreenHouseClass->setStatusBar(statusBar);
        menuBar = new QMenuBar(GreenHouseClass);
        menuBar->setObjectName("menuBar");
        menuBar->setGeometry(QRect(0, 0, 1173, 22));
        GreenHouseClass->setMenuBar(menuBar);

        retranslateUi(GreenHouseClass);

        QMetaObject::connectSlotsByName(GreenHouseClass);
    } // setupUi

    void retranslateUi(QMainWindow *GreenHouseClass)
    {
        GreenHouseClass->setWindowTitle(QCoreApplication::translate("GreenHouseClass", "GreenHouse", nullptr));
        netConfGroupBox->setTitle(QCoreApplication::translate("GreenHouseClass", "\347\275\221\347\273\234\351\205\215\347\275\256", nullptr));
        ipLabel->setText(QString());
#if QT_CONFIG(statustip)
        portLabel->setStatusTip(QString());
#endif // QT_CONFIG(statustip)
#if QT_CONFIG(whatsthis)
        portLabel->setWhatsThis(QString());
#endif // QT_CONFIG(whatsthis)
        portLabel->setText(QString());
        ipEdit->setText(QString());
        groupBox->setTitle(QCoreApplication::translate("GreenHouseClass", "\346\270\251\346\271\277\345\272\246", nullptr));
        openHumAndTemBtn->setText(QCoreApplication::translate("GreenHouseClass", "\345\274\200\345\220\257\346\270\251\346\271\277\345\272\246\346\243\200\346\265\213", nullptr));
        temLabel->setText(QString());
        humLabel->setText(QString());
        groupBox_3->setTitle(QCoreApplication::translate("GreenHouseClass", "\345\234\237\345\243\244\346\271\277\345\272\246", nullptr));
        humSoilLabel->setText(QString());
        openHumSoilBtn->setText(QCoreApplication::translate("GreenHouseClass", "\345\274\200\345\220\257\345\234\237\345\243\244\346\271\277\345\272\246\346\243\200\346\265\213", nullptr));
        openBtn->setText(QCoreApplication::translate("GreenHouseClass", "\347\233\221\345\220\254", nullptr));
        closeBtn->setText(QCoreApplication::translate("GreenHouseClass", "\345\201\234\346\255\242", nullptr));
        groupBox_5->setTitle(QCoreApplication::translate("GreenHouseClass", "\346\216\245\346\224\266\347\252\227\345\217\243", nullptr));
        cleanRecBtn->setText(QString());
        groupBox_6->setTitle(QCoreApplication::translate("GreenHouseClass", "\345\205\211\347\205\247", nullptr));
        lightLabel->setText(QString());
        openLightBtn->setText(QCoreApplication::translate("GreenHouseClass", "\345\274\200\345\220\257\345\205\211\347\205\247\346\243\200\346\265\213", nullptr));
        groupBox_7->setTitle(QCoreApplication::translate("GreenHouseClass", "\350\266\205\345\243\260\346\263\242", nullptr));
        openHCSR04Btn->setText(QCoreApplication::translate("GreenHouseClass", "\345\274\200\345\220\257\350\266\205\345\243\260\346\263\242\346\243\200\346\265\213", nullptr));
        HCSR04Edit->setHtml(QCoreApplication::translate("GreenHouseClass", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><meta charset=\"utf-8\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"hr { height: 1px; border-width: 0; }\n"
"li.unchecked::marker { content: \"\\2610\"; }\n"
"li.checked::marker { content: \"\\2612\"; }\n"
"</style></head><body style=\" font-family:'Microsoft YaHei UI'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><br /></p></body></html>", nullptr));
        HCSR04Label->setText(QString());
        groupBox_8->setTitle(QCoreApplication::translate("GreenHouseClass", "\344\272\272\344\275\223\347\272\242\345\244\226", nullptr));
        openHCSR501Btn->setText(QCoreApplication::translate("GreenHouseClass", "\345\274\200\345\220\257\344\272\272\344\275\223\347\272\242\345\244\226\346\243\200\346\265\213", nullptr));
        HCSR501Label->setText(QString());
        groupBox_9->setTitle(QCoreApplication::translate("GreenHouseClass", "\351\243\216\346\211\207", nullptr));
        level3Btn->setText(QCoreApplication::translate("GreenHouseClass", "3", nullptr));
        fanBtn->setText(QString());
        level2Btn->setText(QCoreApplication::translate("GreenHouseClass", "2", nullptr));
        lineEdit->setText(QCoreApplication::translate("GreenHouseClass", "\351\243\216\346\211\207\345\274\200\345\205\263\360\237\221\206", nullptr));
        level1Btn->setText(QCoreApplication::translate("GreenHouseClass", "1", nullptr));
        groupBox_10->setTitle(QCoreApplication::translate("GreenHouseClass", "\345\217\221\351\200\201\347\252\227\345\217\243", nullptr));
        sendBtn->setText(QString());
        cleanSendBtn->setText(QString());
        cleanAllBtn->setText(QString());
        lineEdit_2->setText(QCoreApplication::translate("GreenHouseClass", "\346\270\205\351\231\244\346\211\200\346\234\211\344\274\240\346\204\237\345\231\250\346\225\260\346\215\256\347\252\227\345\217\243\360\237\221\206", nullptr));
    } // retranslateUi

};

namespace Ui {
    class GreenHouseClass: public Ui_GreenHouseClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GREENHOUSE_H
