#include "loginin.h"
#include "ui_loginin.h"

LoginIn::LoginIn(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LoginIn)
{
    ui->setupUi(this);
}

LoginIn::~LoginIn()
{
    delete ui;
}
