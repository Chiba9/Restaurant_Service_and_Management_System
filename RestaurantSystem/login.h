#ifndef LOGIN_H
#define LOGIN_H

#include "basewindow.h"

namespace Ui {
class Login;
}

class Login : public BaseWindow
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = 0);
    ~Login();

private:
    initTitleBar();
    initMainWindow();

private:
    Ui::Login *ui;

};

#endif // LOGIN_H
