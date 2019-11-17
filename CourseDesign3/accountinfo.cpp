#include "accountinfo.h"
#include "ui_accountinfo.h"
#include "QComboBox"
#include "librarian.h"

accountinfo::accountinfo(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::accountinfo)
{
    ui->setupUi(this);
    this->setWindowTitle(tr("信息修改"));
    this->resize(500, 280);
    QPalette palette = this->palette();
    palette.setColor(QPalette::Window, QColor(255, 255, 255));
    this->setPalette(palette);
    ui->lineEdit_3->setEchoMode(QLineEdit::Password);
    QIcon ico_1("://o.png");
    ui->pushButton->setIcon(ico_1);
    ui->pushButton->setIconSize(QSize(50,50));
    ui->pushButton->setStyleSheet("QPushButton{background-color:white;\
                              color: black;   border-radius: 10px;  border: 2px groove gray;\
                              border-style: outset;}"
                              "QPushButton:hover{background-color:black; color: white;}");
}

accountinfo::~accountinfo()
{
    delete ui;
}
//修改管理员姓名性别
void accountinfo::on_pushButton_clicked()
{
    QString userID = ui->lineEdit->text();
    QString name = ui->lineEdit_2->text();
    QString gender = ui->comboBox->currentText();
    Librarian lib;
    int i,j;
    i=lib.changeName(userID,name);
    j=lib.changeGender(userID,gender);
    if(userID.size()!=9){
        QMessageBox::critical(this,"修改失败","学工号错误！",QMessageBox::Cancel);
    }else{
        if (ui->lineEdit_3->text() == tr("123456")){
            if(i==0 ){
                if(j==0){
                    this->hide();
                    QMessageBox::information(this,"修改成功","您的信息已更新",QMessageBox::Ok);
                }
                else if(j==1){
                    QMessageBox::critical(this,"修改失败","性别错误！",QMessageBox::Cancel);
                }else if(j==2){
                    QMessageBox::critical(this,"修改失败","数据库错误！",QMessageBox::Cancel);
                }else{
                    QMessageBox::critical(this,"修改失败","未知错误！",QMessageBox::Cancel);
                }
            }
            else if(i==1){
                QMessageBox::critical(this,"修改失败","姓名错误！",QMessageBox::Cancel);
            }else if(i==2){
                QMessageBox::critical(this,"修改失败","数据库错误！",QMessageBox::Cancel);
            }else if(i==3){
                QMessageBox::critical(this,"修改失败","学工号不存在！",QMessageBox::Cancel);
            }else{
                QMessageBox::critical(this,"修改失败","未知错误！",QMessageBox::Cancel);
            }
            }
        else
            QMessageBox::critical(this,"修改错误","授权码不正确！",QMessageBox::Cancel);
    }

}
