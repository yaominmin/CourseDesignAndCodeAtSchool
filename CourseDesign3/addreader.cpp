#include "addreader.h"
#include "ui_addreader.h"
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QComboBox>
#include <librarian.h>
#include <QDebug>
addreader::addreader(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addreader)
{
    ui->setupUi(this);
    this->setWindowTitle(tr("添加读者"));
    this->resize(750, 500);
    QPalette palette = this->palette();
    palette.setColor(QPalette::Window, QColor(255, 255, 255));
    this->setPalette(palette);
    ui->tableWidget->clearContents();
    ui->tableWidget->setFocusPolicy(Qt::NoFocus);
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget->setStyleSheet("selection-background-color:lightblue;");
    ui->tableWidget->horizontalHeader()->setStyleSheet("QHeaderView::section{background:skyblue;}");
    QStringList sexList;
    sexList<<"男"<<"女";
    for(int i = 0;i <= 15;i++){
        QComboBox *sex=new QComboBox();
        sex->addItems(sexList);
        ui->tableWidget->setCellWidget(i,2,sex);
    }
    QStringList deptList;
    deptList<<"软件"<<"计算机";
    for(int i = 0;i <= 15;i++){
        QComboBox *dept=new QComboBox();
        dept->addItems(deptList);
        ui->tableWidget->setCellWidget(i,3,dept);
    }
    QStringList typeList;
    typeList<<"学生"<<"老师";
    for(int i = 0;i <= 15;i++){
        QComboBox *type=new QComboBox();
        type->addItems(typeList);
        ui->tableWidget->setCellWidget(i,4,type);
    }
    ui->pushButton_2->setToolTip("按住CTRL进行多选");
    QIcon ico_1("://o.png");
    ui->pushButton->setIcon(ico_1);
    ui->pushButton->setIconSize(QSize(50,50));
    QIcon ico_2("://b.png");
    ui->tableWidget->setFocusPolicy(Qt::NoFocus);
    ui->pushButton_2->setIcon(ico_2);
    ui->pushButton_2->setIconSize(QSize(50,50));
    ui->pushButton_2->setStyleSheet("QPushButton{background-color:white;\
                              color: black;   border-radius: 10px;  border: 2px groove gray;\
                              border-style: outset;}"
                              "QPushButton:hover{background-color:black; color: white;}");
    ui->pushButton->setStyleSheet("QPushButton{background-color:white;\
                              color: black;   border-radius: 10px;  border: 2px groove gray;\
                              border-style: outset;}"
                              "QPushButton:hover{background-color:black; color: white;}");
}

addreader::~addreader()
{
    delete ui;
}


void addreader::on_pushButton_clicked()
{
    QTableWidgetItem f;
    f.setText("");
    int b=-1;
    for(int i=0;i<20;i++)
    {
        if(ui->tableWidget->item(i,0)==NULL||ui->tableWidget->item(i,1)==NULL||ui->tableWidget->item(i,0)->text()==f.text()||ui->tableWidget->item(i,1)->text()==f.text())
            continue;
        QTableWidgetItem *c=new QTableWidgetItem();
        c=ui->tableWidget->item(i,0);
        QTableWidgetItem *d=new QTableWidgetItem();
        d=ui->tableWidget->item(i,1);
        QString userID=c->text();
        QString name=d->text();

        QWidget *widgetSex=ui->tableWidget->cellWidget(i,2);
        QComboBox *sex=(QComboBox*)widgetSex;
        QString userSex=sex->currentText();

        QWidget *widgetDept=ui->tableWidget->cellWidget(i,3);
        QComboBox *Dept=(QComboBox*)widgetDept;
        QString userDept=Dept->currentText();

        QWidget *widgetType=ui->tableWidget->cellWidget(i,4);
        QComboBox *Type=(QComboBox*)widgetType;
        QString userType=Type->currentText();
        QString status="正常";
        Librarian lib;
        b=lib.createReader(userID,name,userSex,userDept,userType,status);
    }
    if(b==-1){
        QMessageBox::critical(this,"添加错误","无完整数据！",QMessageBox::Ok);
    }else if(b==0){
        QMessageBox::information(this,"添加成功","已成功添加有完整信息读者！",QMessageBox::Ok);
    }else{
        QMessageBox::information(this,"添加失败","数据库插入错误！",QMessageBox::Ok);
    }
//    if(ui->tableWidget->item(0,0) == NULL){
//        QMessageBox::critical(this,"添加错误","必填内容不能为空！",QMessageBox::Ok);
//    }
//    else
//        QMessageBox::information(this,"添加成功","您已成功添加读者！",QMessageBox::Ok);
//    QWidget *widgetSex=ui->tableWidget->cellWidget(0,2);
//    QComboBox *sex=(QComboBox*)widgetSex;
//    QString a=sex->currentText();
//    qDebug()<<a;
}

void addreader::on_pushButton_2_clicked()
{
    bool focus = ui->tableWidget->isItemSelected(ui->tableWidget->currentItem());
    if(!focus){
        QMessageBox::critical(this,"失败提示","请在检索并选择后进行操作！",QMessageBox::Ok);
    }
    else{
        QList<QTableWidgetSelectionRange>ranges = ui->tableWidget->selectedRanges();
        int count=ranges.count();
        //qDebug()<<count;
        int select[20];
        for(int i=0;i<20;i++)
            select[i]=-1;
        /*
         for(int i=0;i<20;i++)
            qDebug()<<select[i];
        */
        for(int i=0;i<count;i++)
        {
            select[i]=ranges.at(i).topRow();
            /*int topRow=ranges.at(i).topRow();
            qDebug()<<"selectRow"<<topRow;
            int topRow=ranges.at(i).topRow();
            int bottomRow=ranges.at(i).bottomRow();
            for(int j=topRow;j<=bottomRow;j++)
            {
               qDebug()<<"selectRow"<<j;
            }*/
        }
        /*
        for(int i=0;i<count;i++){
            qDebug()<<"selectRow"<<select[i];
        }
        */
        for(int i=count-1;i>=0;i--){
            //ui->tableWidget->removeRow(select[i]);
            ui->tableWidget->setItem(select[i],0,NULL);
            ui->tableWidget->setItem(select[i],1,NULL);
        }
    }
}
