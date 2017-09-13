/********************************************************************************
** Form generated from reading UI file 'mytitlebar.ui'
**
** Created by: Qt User Interface Compiler version 5.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MYTITLEBAR_H
#define UI_MYTITLEBAR_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MyTitleBar
{
public:

    void setupUi(QWidget *MyTitleBar)
    {
        if (MyTitleBar->objectName().isEmpty())
            MyTitleBar->setObjectName(QStringLiteral("MyTitleBar"));
        MyTitleBar->resize(400, 300);

        retranslateUi(MyTitleBar);

        QMetaObject::connectSlotsByName(MyTitleBar);
    } // setupUi

    void retranslateUi(QWidget *MyTitleBar)
    {
        MyTitleBar->setWindowTitle(QApplication::translate("MyTitleBar", "Form", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MyTitleBar: public Ui_MyTitleBar {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MYTITLEBAR_H
