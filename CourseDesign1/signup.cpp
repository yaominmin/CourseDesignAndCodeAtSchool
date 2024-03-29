﻿#include "signup.h"
#include "ui_signup.h"
#include <QDebug>
#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QString>

signup::signup(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::signup)
{
    this->setWindowIcon(QIcon(":/images/bitbug_favicon.ico"));
    ui->setupUi(this);
    ui->lineEdit_id->setPlaceholderText("6~10字母数字)");
}

signup::~signup()
{
    delete ui;
}

void signup::on_pushButton_2_clicked()
{
    close();
}

void signup::on_pushButton_clicked()
{
    QString id=ui->lineEdit_id->text();                                  //id
    QString password=ui->lineEdit_password->text();                      //passsword
    QString name=ui->lineEdit_username->text();                           //username
    QString useridnum=ui->lineEdit_useridnum->text();                     //useridnum
    QString usersex=ui->comboBox_usersex->currentText();                  //usersex
    QString usertel=ui->lineEdit_usertel->text();
    if(id.isEmpty()==0||password.isEmpty()==0||name.isEmpty()==0)
    {
        int k=0;
        QSqlQuery query;
        query.exec("select * from user");
        while(query.next())
        {
            QString name=query.value(0).toString();
            if(id==name){
              QMessageBox::warning(this, tr("错误"),tr("用户已存在!"));
              ui->lineEdit_id->clear();
              ui->lineEdit_id->setFocus();//给一个输入焦点
              ui->lineEdit_password->clear();
              ui->lineEdit_password->setFocus();
              ui->lineEdit_useridnum->clear();
              ui->lineEdit_useridnum->setFocus();
              ui->lineEdit_username->clear();
              ui->lineEdit_username->setFocus();
              ui->lineEdit_usertel->clear();
              ui->lineEdit_usertel->setFocus();
              ui->lineEdit_id->setFocus();
              k=1;
              break;
             }
       }
        if(k!=1)
        {
           QSqlQuery query2;//password  username useridnum usersex  usertel
           query2.prepare("insert into "
                          "user(id,password,username,useridnum,usersex,usertel) "
                          "values(?,?,?,?,?,?)");
           query2.addBindValue(id);
           query2.addBindValue(password);
           query2.addBindValue(name);
           query2.addBindValue(useridnum);
           query2.addBindValue(usersex);
           query2.addBindValue(usertel);
           query2.exec();
           QMessageBox::warning(this, tr("恭喜"),tr("注册成功!"));
           close();
        }
    }
    else
     {
        QMessageBox::warning(this,tr("警告"),tr("用户名或密码为空!"));
        ui->lineEdit_id->setFocus();
        ui->lineEdit_password->setFocus();
     }
}
