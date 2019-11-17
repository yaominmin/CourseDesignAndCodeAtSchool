#ifndef LOGIN_H
#define LOGIN_H
#include <QDialog>
#include <QMessageBox>
#include <doublelinklist.h>
#include <cstdlib>

//客户端登录所需要的定义和函数

namespace Ui
{
class Login;
}

class Login : public QDialog
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = 0);
    ~Login();

    void dosend();

signals:
    void send();

protected:
    int CheckWriting();//查看账号密码栏是否为空
    int CheckAccount();//查看账号密码是否正确
    //unsigned int BKDRHash(char* str);//利用哈希函数将密码加密

    //槽
private slots:
    void on_quitbutton_clicked();//点击退出按钮所做出的反应
    void on_loginbutton_clicked();//点击登陆所做出的反应

private:
    enum LoginType { Success, WebError, AccountBlank, AccountWrong, PasswordBlank, PasswordWrong, RepeatError };

private:
    Ui::Login* ui;
};


#endif // LOGIN_H
