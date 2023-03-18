/********************************************************************************
** Form generated from reading UI file 'autoreporting.ui'
**
** Created by: Qt User Interface Compiler version 5.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_AUTOREPORTING_H
#define UI_AUTOREPORTING_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>
#include "qcameraviewfinder.h"

QT_BEGIN_NAMESPACE

class Ui_autoreporting
{
public:
    QCameraViewfinder *widget;
    QPushButton *button_ok;
    QComboBox *comboBox_cameralist;
    QPushButton *button_close;
    QLabel *label_cameralist;
    QPushButton *button_grab;
    QLabel *label_ba;
    QLabel *label_score;
    QLabel *label_result;
    QLabel *label_hu;
    QListWidget *list_history;
    QLabel *label;
    QCheckBox *checkBox;
    QCheckBox *checkBox_2;
    QLabel *label_2;
    QLabel *label_3;
    QPushButton *pushButton;

    void setupUi(QWidget *autoreporting)
    {
        if (autoreporting->objectName().isEmpty())
            autoreporting->setObjectName(QStringLiteral("autoreporting"));
        autoreporting->resize(1150, 490);
        autoreporting->setMinimumSize(QSize(1150, 490));
        autoreporting->setMaximumSize(QSize(1150, 490));
        widget = new QCameraViewfinder(autoreporting);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(20, 80, 601, 391));
        button_ok = new QPushButton(autoreporting);
        button_ok->setObjectName(QStringLiteral("button_ok"));
        button_ok->setGeometry(QRect(350, 10, 171, 31));
        QFont font;
        font.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font.setBold(false);
        font.setWeight(50);
        button_ok->setFont(font);
        comboBox_cameralist = new QComboBox(autoreporting);
        comboBox_cameralist->setObjectName(QStringLiteral("comboBox_cameralist"));
        comboBox_cameralist->setGeometry(QRect(110, 10, 231, 31));
        QFont font1;
        font1.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        comboBox_cameralist->setFont(font1);
        button_close = new QPushButton(autoreporting);
        button_close->setObjectName(QStringLiteral("button_close"));
        button_close->setGeometry(QRect(940, 10, 181, 31));
        button_close->setFont(font);
        label_cameralist = new QLabel(autoreporting);
        label_cameralist->setObjectName(QStringLiteral("label_cameralist"));
        label_cameralist->setGeometry(QRect(30, 10, 91, 31));
        QFont font2;
        font2.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font2.setPointSize(10);
        font2.setBold(false);
        font2.setWeight(50);
        label_cameralist->setFont(font2);
        button_grab = new QPushButton(autoreporting);
        button_grab->setObjectName(QStringLiteral("button_grab"));
        button_grab->setGeometry(QRect(530, 10, 401, 31));
        QFont font3;
        font3.setBold(true);
        font3.setWeight(75);
        button_grab->setFont(font3);
        label_ba = new QLabel(autoreporting);
        label_ba->setObjectName(QStringLiteral("label_ba"));
        label_ba->setGeometry(QRect(650, 90, 251, 351));
        label_score = new QLabel(autoreporting);
        label_score->setObjectName(QStringLiteral("label_score"));
        label_score->setGeometry(QRect(950, 130, 101, 101));
        QFont font4;
        font4.setFamily(QStringLiteral("Microsoft YaHei"));
        font4.setPointSize(69);
        font4.setBold(true);
        font4.setItalic(false);
        font4.setUnderline(false);
        font4.setWeight(75);
        label_score->setFont(font4);
        label_score->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        label_result = new QLabel(autoreporting);
        label_result->setObjectName(QStringLiteral("label_result"));
        label_result->setGeometry(QRect(930, 100, 81, 31));
        QFont font5;
        font5.setFamily(QStringLiteral("Microsoft YaHei"));
        font5.setPointSize(13);
        font5.setBold(true);
        font5.setWeight(75);
        label_result->setFont(font5);
        label_hu = new QLabel(autoreporting);
        label_hu->setObjectName(QStringLiteral("label_hu"));
        label_hu->setGeometry(QRect(1060, 190, 54, 41));
        QFont font6;
        font6.setFamily(QStringLiteral("Microsoft YaHei"));
        font6.setPointSize(15);
        font6.setBold(true);
        font6.setWeight(75);
        label_hu->setFont(font6);
        label_hu->setStyleSheet(QStringLiteral(""));
        list_history = new QListWidget(autoreporting);
        list_history->setObjectName(QStringLiteral("list_history"));
        list_history->setGeometry(QRect(930, 300, 181, 141));
        QFont font7;
        font7.setPointSize(13);
        font7.setBold(true);
        font7.setWeight(75);
        list_history->setFont(font7);
        label = new QLabel(autoreporting);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(930, 250, 81, 31));
        label->setFont(font5);
        checkBox = new QCheckBox(autoreporting);
        checkBox->setObjectName(QStringLiteral("checkBox"));
        checkBox->setGeometry(QRect(940, 60, 111, 31));
        QFont font8;
        font8.setFamily(QStringLiteral("Microsoft YaHei"));
        font8.setPointSize(11);
        checkBox->setFont(font8);
        checkBox_2 = new QCheckBox(autoreporting);
        checkBox_2->setObjectName(QStringLiteral("checkBox_2"));
        checkBox_2->setGeometry(QRect(1050, 60, 181, 31));
        checkBox_2->setFont(font8);
        label_2 = new QLabel(autoreporting);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(20, 50, 101, 31));
        label_2->setFont(font5);
        label_3 = new QLabel(autoreporting);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(640, 60, 81, 21));
        label_3->setFont(font5);
        pushButton = new QPushButton(autoreporting);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(1020, 250, 91, 31));
        QFont font9;
        font9.setFamily(QStringLiteral("Microsoft YaHei"));
        font9.setPointSize(13);
        font9.setBold(false);
        font9.setWeight(50);
        pushButton->setFont(font9);

        retranslateUi(autoreporting);

        QMetaObject::connectSlotsByName(autoreporting);
    } // setupUi

    void retranslateUi(QWidget *autoreporting)
    {
        autoreporting->setWindowTitle(QApplication::translate("autoreporting", "Autoreporting", Q_NULLPTR));
        button_ok->setText(QApplication::translate("autoreporting", "\346\211\223\345\274\200\346\221\204\345\203\217\345\244\264", Q_NULLPTR));
        button_close->setText(QApplication::translate("autoreporting", "\345\205\263\351\227\255\346\221\204\345\203\217\345\244\264", Q_NULLPTR));
        label_cameralist->setText(QApplication::translate("autoreporting", "\345\275\223\345\211\215\346\221\204\345\203\217\345\244\264\357\274\232", Q_NULLPTR));
        button_grab->setText(QApplication::translate("autoreporting", "GRAB", Q_NULLPTR));
        label_ba->setText(QString());
        label_score->setText(QString());
        label_result->setText(QApplication::translate("autoreporting", "\346\210\220\347\273\251", Q_NULLPTR));
        label_hu->setText(QApplication::translate("autoreporting", "\347\216\257", Q_NULLPTR));
        label->setText(QApplication::translate("autoreporting", "\345\216\206\345\217\262\346\210\220\347\273\251", Q_NULLPTR));
        checkBox->setText(QApplication::translate("autoreporting", "\350\203\270\347\216\257\351\235\266", Q_NULLPTR));
        checkBox_2->setText(QApplication::translate("autoreporting", "\347\216\257\345\275\242\351\235\266", Q_NULLPTR));
        label_2->setText(QApplication::translate("autoreporting", "\346\221\204\345\203\217\345\244\264\351\242\204\350\247\210", Q_NULLPTR));
        label_3->setText(QApplication::translate("autoreporting", "\347\273\223\346\236\234\351\242\204\350\247\210", Q_NULLPTR));
        pushButton->setText(QApplication::translate("autoreporting", "\346\270\205\347\251\272", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class autoreporting: public Ui_autoreporting {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_AUTOREPORTING_H
