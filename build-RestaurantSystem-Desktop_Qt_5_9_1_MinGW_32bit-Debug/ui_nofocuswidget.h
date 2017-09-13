/********************************************************************************
** Form generated from reading UI file 'nofocuswidget.ui'
**
** Created by: Qt User Interface Compiler version 5.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NOFOCUSWIDGET_H
#define UI_NOFOCUSWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QTreeView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_NoFocusWidget
{
public:
    QDialogButtonBox *buttonBox;
    QRadioButton *radioButton;
    QTreeView *treeView;

    void setupUi(QWidget *NoFocusWidget)
    {
        if (NoFocusWidget->objectName().isEmpty())
            NoFocusWidget->setObjectName(QStringLiteral("NoFocusWidget"));
        NoFocusWidget->resize(400, 300);
        buttonBox = new QDialogButtonBox(NoFocusWidget);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setGeometry(QRect(170, 200, 193, 28));
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        radioButton = new QRadioButton(NoFocusWidget);
        radioButton->setObjectName(QStringLiteral("radioButton"));
        radioButton->setGeometry(QRect(240, 40, 115, 19));
        treeView = new QTreeView(NoFocusWidget);
        treeView->setObjectName(QStringLiteral("treeView"));
        treeView->setGeometry(QRect(60, 90, 256, 192));

        retranslateUi(NoFocusWidget);

        QMetaObject::connectSlotsByName(NoFocusWidget);
    } // setupUi

    void retranslateUi(QWidget *NoFocusWidget)
    {
        NoFocusWidget->setWindowTitle(QApplication::translate("NoFocusWidget", "Form", Q_NULLPTR));
        radioButton->setText(QApplication::translate("NoFocusWidget", "RadioButton", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class NoFocusWidget: public Ui_NoFocusWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NOFOCUSWIDGET_H
