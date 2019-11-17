#include "login.h"
#include <iostream>

#include "ui_login.h"//ui界面占时没有实现
#include <QMessageBox>

Login::Login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);
    setWindowTitle("航空售票系统登录");
    ui->passwordtext->setEchoMode(QLineEdit::Password);


}

Login::~Login()
{
    disconnect(this, SIGNAL(send()), this, SLOT(close()));
    disconnect(this, SIGNAL(send()), this, SLOT(deleteLater()));

    delete ui;
    ui = nullptr;

    std::cout << "delete Login" << std::endl;
}

int Login::CheckWriting()
{
    if (ui->accounttext->text() == "")
    {
        QMessageBox(QMessageBox::Warning, "账号错误", "账号为空，请输入账号", QMessageBox::Ok).exec();
        return AccountBlank;
    }
    if (ui->passwordtext->text() == "")
    {
        QMessageBox(QMessageBox::Warning, "密码错误", "密码为空，请输入密码", QMessageBox::Ok).exec();
        return PasswordBlank;
    }
    if (ui->accounttext->text() == ui->passwordtext->text())
    {
        QMessageBox(QMessageBox::Warning, "重复错误", "账号密码不得相同", QMessageBox::Ok).exec();
        return RepeatError;
    }
    return Success;
}

int Login::CheckAccount()
{

}

/*
 * 登陆密码

 */
//unsigned int Login::BKDRHash(char* str)
//{
//    unsigned int seed = 131; // 31 131 1313 13131 131313 etc..
//    unsigned int hash = 0;

//    while (*str)
//        hash = hash * seed + (*str++);

//    return (hash & 0x7FFFFFFF);
//}

void Login::on_loginbutton_clicked()
{
    if (Success != CheckWriting() )
        return;

    int flag = CheckAccount();
    if (Success == flag)
        dosend();
//    else if (WebError == flag)
//        QMessageBox(QMessageBox::Warning, "查询失败",  QMessageBox::Ok).exec();
//    else if (AccountWrong == flag)
//        QMessageBox(QMessageBox::Warning, "输入错误",  QMessageBox::Ok).exec();
    else if (PasswordWrong == flag)
        QMessageBox(QMessageBox::Warning, "输入错误", "密码错误，请检查密码是否正确后重新输入!", QMessageBox::Ok).exec();
}

void Login::on_quitbutton_clicked()
{
    exit(0);
}

//发送自定义信号
void Login::dosend()
{
    emit send();
}
