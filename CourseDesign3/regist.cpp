#include "regist.h"
#include "ui_regist.h"
#include "QComboBox"
#include "librarian.h"

regist::regist(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::regist)
{
    ui->setupUi(this);
    this->setWindowTitle(tr("添加管理员"));
    this->resize(500, 400);
    QPalette palette = this->palette();
    palette.setColor(QPalette::Window, QColor(255, 255, 255));
    this->setPalette(palette);
    ui->lineEdit_2->setEchoMode(QLineEdit::Password);
    ui->lineEdit_3->setEchoMode(QLineEdit::Password);
    ui->lineEdit_5->setEchoMode(QLineEdit::Password);
    QIcon ico_1("://o.png");
    ui->pushButton->setIcon(ico_1);
    ui->pushButton->setIconSize(QSize(50,50));
    ui->pushButton->setStyleSheet("QPushButton{background-color:white;\
                              color: black;   border-radius: 10px;  border: 2px groove gray;\
                              border-style: outset;}"
                              "QPushButton:hover{background-color:black; color: white;}");
}

regist::~regist()
{
    delete ui;
}


void regist::on_pushButton_clicked()
{
    if (ui->lineEdit_3->text() == tr("123456")){

        QString userID = ui->lineEdit->text();
        QString password = ui->lineEdit_2->text();
        QString name = ui->lineEdit_4->text();
        QString passwordagain = ui->lineEdit_5->text();
        QString sex = ui->comboBox->currentText();
        Librarian lib;
        int i;
        if(password!=passwordagain){
            QMessageBox::critical(this,"注册失败","密码不一致！",QMessageBox::Cancel);
        }
        else{
            //注册管理员，
            i=lib.createLibrarian(userID,name, sex, password);
            if(i == 0){
                this->hide();
                QMessageBox::information(this,"注册成功","您已成功注册",QMessageBox::Ok);

            }else if(i==1){
                QMessageBox::critical(this,"注册失败","学工号错误！",QMessageBox::Cancel);
            }else if(i==2){
                QMessageBox::critical(this,"注册失败","姓名错误！",QMessageBox::Cancel);
            }else if(i==3){
                QMessageBox::critical(this,"注册失败","性别错误！",QMessageBox::Cancel);
            }else if(i==4){
                QMessageBox::critical(this,"注册失败","密码长度错误！",QMessageBox::Cancel);
            }else if(i==5){
                QMessageBox::critical(this,"注册失败","学工号重复！",QMessageBox::Cancel);
            }
            else
                QMessageBox::critical(this,"注册失败","未知错误！",QMessageBox::Cancel);
            }
        }
    else
        QMessageBox::critical(this,"注册错误","授权码不正确！",QMessageBox::Cancel);
}
