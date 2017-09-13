#include "login.h"
#include "ui_login.h"
#include<QLineEdit>
#include<QString>
#include<QStringList>

Login::Login(QWidget *parent) :
    BaseWindow(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);

    initTitleBar();
    initMainWindow();
}

Login::~Login()
{
    delete ui;
}

Login::initTitleBar()
{
    m_titleBar->move(0,0);
    m_titleBar->raise();
    m_titleBar->setBackgroundColor(0,0,0,true);
    m_titleBar->setButtonType(MIN_BUTTON);
    m_titleBar->setTitleWidth(this->width());


}

Login::initMainWindow()
{
    ui->comboBox_UserName->setEditable(true);
    QLineEdit* lineEdit = ui->comboBox_UserName->lineEdit();
    lineEdit->setPlaceholderText("用户名/手机号");
    ui->lineEdit_PassWord->setPlaceholderText("密码");
    QStringList types;
    types << "顾客" << "服务员" << "厨师" << "经理" << "管理员";
    ui->comboBox_Type->addItems(types);

}
