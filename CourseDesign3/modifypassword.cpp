#include "modifypassword.h"
#include "ui_modifypassword.h"
#include "librarian.h"

modifypassword::modifypassword(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::modifypassword)
{
    ui->setupUi(this);
    this->setWindowTitle(tr("修改密码"));
    this->resize(500, 280);
    QPalette palette = this->palette();
    palette.setColor(QPalette::Window, QColor(255, 255, 255));
    this->setPalette(palette);
    ui->lineEdit_6->setEchoMode(QLineEdit::Password);
    ui->lineEdit_3->setEchoMode(QLineEdit::Password);
    ui->lineEdit_5->setEchoMode(QLineEdit::Password);
    QIcon ico_2("://p.png");
    ui->pushButton->setIcon(ico_2);
    ui->pushButton->setIconSize(QSize(50,40));
    ui->pushButton->setStyleSheet("QPushButton{background-color:white;\
                              color: black;   border-radius: 10px;  border: 2px groove gray;\
                              border-style: outset;}"
                              "QPushButton:hover{background-color:black; color: white;}");
}

modifypassword::~modifypassword()
{
    delete ui;
}

//忘记密码
void modifypassword::on_pushButton_clicked()
{
    QString userID = ui->lineEdit_4->text();
    QString password = ui->lineEdit_3->text();
    QString passwordagain = ui->lineEdit_5->text();
    Librarian lib;
    int i;
    if (ui->lineEdit_6->text() == tr("123456")){
        i=lib.changePassword(userID,password,passwordagain);
        if(i==0){
            this->hide();
            QMessageBox::information(this,"修改成功","您已成功更改密码",QMessageBox::Ok);
        }else if(i==1){
            QMessageBox::critical(this,"注册失败","密码不一致！",QMessageBox::Cancel);
        }else if(i==2){
            QMessageBox::critical(this,"注册失败","数据库错误！",QMessageBox::Cancel);
        }else
            QMessageBox::critical(this,"注册失败","未知错误！",QMessageBox::Cancel);
        }
    else
        QMessageBox::critical(this,"修改错误","授权码不正确！",QMessageBox::Cancel);
}
