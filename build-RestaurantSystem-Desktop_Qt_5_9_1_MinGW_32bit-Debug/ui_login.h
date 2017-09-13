/********************************************************************************
** Form generated from reading UI file 'login.ui'
**
** Created by: Qt User Interface Compiler version 5.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGIN_H
#define UI_LOGIN_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Login
{
public:
    QComboBox *comboBox_UserName;
    QLineEdit *lineEdit_PassWord;
    QPushButton *pushButton_Login;
    QPushButton *pushButton_Register;
    QComboBox *comboBox_Type;

    void setupUi(QWidget *Login)
    {
        if (Login->objectName().isEmpty())
            Login->setObjectName(QStringLiteral("Login"));
        Login->resize(500, 350);
        comboBox_UserName = new QComboBox(Login);
        comboBox_UserName->setObjectName(QStringLiteral("comboBox_UserName"));
        comboBox_UserName->setGeometry(QRect(130, 180, 200, 30));
        lineEdit_PassWord = new QLineEdit(Login);
        lineEdit_PassWord->setObjectName(QStringLiteral("lineEdit_PassWord"));
        lineEdit_PassWord->setGeometry(QRect(130, 210, 200, 30));
        pushButton_Login = new QPushButton(Login);
        pushButton_Login->setObjectName(QStringLiteral("pushButton_Login"));
        pushButton_Login->setGeometry(QRect(140, 260, 180, 30));
        pushButton_Register = new QPushButton(Login);
        pushButton_Register->setObjectName(QStringLiteral("pushButton_Register"));
        pushButton_Register->setGeometry(QRect(340, 213, 100, 25));
        comboBox_Type = new QComboBox(Login);
        comboBox_Type->setObjectName(QStringLiteral("comboBox_Type"));
        comboBox_Type->setGeometry(QRect(340, 182, 100, 25));

        retranslateUi(Login);

        QMetaObject::connectSlotsByName(Login);
    } // setupUi

    void retranslateUi(QWidget *Login)
    {
        Login->setWindowTitle(QApplication::translate("Login", "Form", Q_NULLPTR));
        comboBox_UserName->setCurrentText(QString());
        lineEdit_PassWord->setText(QString());
        pushButton_Login->setText(QApplication::translate("Login", "\347\231\273   \351\231\206", Q_NULLPTR));
        pushButton_Register->setText(QApplication::translate("Login", "\346\263\250\345\206\214\350\264\246\345\217\267", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class Login: public Ui_Login {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGIN_H
