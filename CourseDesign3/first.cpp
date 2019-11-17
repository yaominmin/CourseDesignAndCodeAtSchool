#include "first.h"
#include "ui_first.h"
#include <QMovie>
#include "user.h"

First::First(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::First)
{
    ui->setupUi(this);
    this->setWindowTitle(tr("用户登录"));
    this->resize(500, 300);
    QPalette palette = this->palette();
    palette.setColor(QPalette::Window, QColor(255, 255, 255));
    this->setPalette(palette);
    ui->lineEdit->setText("111111111");
    ui->lineEdit_2->setText("1234");
    ui->lineEdit_2->setEchoMode(QLineEdit::Password);                         //设置暗文不可见
    ui->lineEdit->setPlaceholderText(QStringLiteral("账号"));
    ui->lineEdit_2->setPlaceholderText(QStringLiteral("密码"));
    QMovie *movie = new QMovie();
    movie->setFileName("://image/pictures/b.gif");
    ui->label->setMovie(movie);
    movie->start();
    ui->label->move(0, 0);
    QIcon ico("://a.jpg");
    ui->pushButton->setIcon(ico);
    ui->pushButton->setIconSize(QSize(50,50));
    QIcon ico_1("://s.jpg");
    ui->pushButton_2->setIcon(ico_1);
    ui->pushButton_2->setIconSize(QSize(50,50));
    QIcon ico_2("://login.png");
    ui->pushButton_3->setIcon(ico_2);
    ui->pushButton_3->setIconSize(QSize(50,50));
    ui->pushButton_3->setStyleSheet("QPushButton{background-color:white;\
                                  color: black;   border-radius: 10px;  border: 2px groove gray;\
                                  border-style: outset;}"
                                  "QPushButton:hover{background-color:black; color: white;}");
    ui->pushButton_4->setStyleSheet("QPushButton{background-color:white;\
                              color: black;   border-radius: 10px;  border: 2px groove gray;\
                              border-style: outset;}"
                              "QPushButton:hover{background-color:black; color: white;}");
    ui->pushButton_5->setStyleSheet("QPushButton{background-color:white;\
                              color: black;   border-radius: 10px;  border: 2px groove gray;\
                              border-style: outset;}"
                              "QPushButton:hover{background-color:black; color: white;}");

}

First::~First()
{
    delete ui;
}

//登录按钮
void First::on_pushButton_3_clicked()
{
    User user;
    QString userID = ui->lineEdit->text();
    QString password = ui->lineEdit_2->text();
    int i = user.login(userID,password);
    //success
    if(i==1){
        this->hide();
        w.show();
    }else if(i==2){
        QMessageBox::critical(this,"错误提示","密码不正确！请重新输入",QMessageBox::Ok);
    }else if(i==0){
        QMessageBox::critical(this,"错误提示","账号不存在！请重新输入",QMessageBox::Ok);
    }else if(i==3){
        QMessageBox::critical(this,"错误提示","未知错误！",QMessageBox::Ok);
    }
}

void First::on_pushButton_5_clicked()
{
    regist dia;
    dia.exec();
}

void First::on_pushButton_4_clicked()
{
    modifypassword dia;
    dia.exec();
}
