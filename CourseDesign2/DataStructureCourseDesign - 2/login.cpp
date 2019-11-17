#include "login.h"
#include <iostream>

#include "ui_login.h"//ui����ռʱû��ʵ��
#include <QMessageBox>

Login::Login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);
    setWindowTitle("������Ʊϵͳ��¼");
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
        QMessageBox(QMessageBox::Warning, "�˺Ŵ���", "�˺�Ϊ�գ��������˺�", QMessageBox::Ok).exec();
        return AccountBlank;
    }
    if (ui->passwordtext->text() == "")
    {
        QMessageBox(QMessageBox::Warning, "�������", "����Ϊ�գ�����������", QMessageBox::Ok).exec();
        return PasswordBlank;
    }
    if (ui->accounttext->text() == ui->passwordtext->text())
    {
        QMessageBox(QMessageBox::Warning, "�ظ�����", "�˺����벻����ͬ", QMessageBox::Ok).exec();
        return RepeatError;
    }
    return Success;
}

int Login::CheckAccount()
{

}

/*
 * ��½����

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
//        QMessageBox(QMessageBox::Warning, "��ѯʧ��",  QMessageBox::Ok).exec();
//    else if (AccountWrong == flag)
//        QMessageBox(QMessageBox::Warning, "�������",  QMessageBox::Ok).exec();
    else if (PasswordWrong == flag)
        QMessageBox(QMessageBox::Warning, "�������", "����������������Ƿ���ȷ����������!", QMessageBox::Ok).exec();
}

void Login::on_quitbutton_clicked()
{
    exit(0);
}

//�����Զ����ź�
void Login::dosend()
{
    emit send();
}
