#include "borrowbook.h"
#include "ui_borrowbook.h"
#include "dboperation.h"
#include "mainwindow.h"
#include <QDebug>
#include "librarian.h"
#include "searchbyisbn.h"
borrowbook::borrowbook(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::borrowbook)
{
    ui->setupUi(this);
    this->setWindowTitle(tr("借阅书籍"));
    this->resize(1000, 400);
    QPalette palette = this->palette();
    palette.setColor(QPalette::Window, QColor(255, 255, 255));
    this->setPalette(palette);
    ui->tableWidget->setShowGrid(true);
    ui->tableWidget->setFocusPolicy(Qt::NoFocus);
    ui->tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);                               //每次选择一行
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);                                //每次选择一行
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);    
    ui->tableWidget->verticalHeader()->setDefaultSectionSize(60);
    ui->tableWidget->horizontalHeader()->setDefaultSectionSize(160);
    ui->tableWidget->setStyleSheet("selection-background-color:lightblue;");
    ui->tableWidget->horizontalHeader()->setStyleSheet("QHeaderView::section{background:skyblue;}");
    ui->pushButton_2->setToolTip("按住CTRL进行多选");
    QIcon ico_6("://image/pictures/hit.PNG");
    ui->pushButton_4->setIcon(ico_6);
    ui->pushButton_4->setIconSize(QSize(280,60));
    ui->pushButton_2->setStyleSheet("QPushButton{background-color:white;\
                              color: black;   border-radius: 10px;  border: 2px groove gray;\
                              border-style: outset;}"
                              "QPushButton:hover{background-color:black; color: white;}");
    ui->pushButton_5->setStyleSheet("QPushButton{background-color:white;\
                              color: black;   border-radius: 10px;  border: 2px groove gray;\
                              border-style: outset;}"
                              "QPushButton:hover{background-color:black; color: white;}");    
}

borrowbook::~borrowbook()
{
    delete ui;
}
void borrowbook::receiveData(QStringList* date)
{
    this->date=date;
    for(int i = 0;i<date->size();i++)
    {
       ui->tableWidget->setItem(i,1,new QTableWidgetItem(QString (date->at(i))));
    }
    ui->tableWidget->setRowCount(date->size());
    QTableWidgetItem f;
    f.setText("");
    Book * book[20];
    for(int i=0;i<20;i++)
    {
        book[i]=new Book();
    }
    for(int i=0;i<date->size();i++){
        if(ui->tableWidget->item(i,1)==nullptr||ui->tableWidget->item(i,1)->text()==f.text())
            continue;
        QTableWidgetItem *c=new QTableWidgetItem();
        c=ui->tableWidget->item(i,1);
        QString ISBN=c->text();
        SearchByISBN byISBN;
        int p=0;
        p = byISBN.search(ISBN,book[i]);
        ui->tableWidget->setItem(i,0,new QTableWidgetItem(book[i]->getBookName()));
        ui->tableWidget->setItem(i,2,new QTableWidgetItem(book[i]->getAuthor()));
        ui->tableWidget->setItem(i,3,new QTableWidgetItem(book[i]->getPublisher()));
        QString str="";
        str=QString::number(book[i]->getAvailable());
        if(str == nullptr){
            break;
        }
        ui->tableWidget->setItem(i,4,new QTableWidgetItem(str));
    }
    ui->tableWidget->resizeColumnsToContents();
}

void borrowbook::on_pushButton_2_clicked()
{
    bool focus = ui->tableWidget->isItemSelected(ui->tableWidget->currentItem());
    if(!focus){
        QMessageBox::critical(this,"失败提示","请在选中后进行操作！",QMessageBox::Ok);
    }
    else{
        QList<QTableWidgetSelectionRange>ranges = ui->tableWidget->selectedRanges();
        int count=ranges.count();
        int select[20];
        for(int i=0;i<20;i++)
            select[i]=-1;
        for(int i=0;i<count;i++)
            select[i]=ranges.at(i).topRow();
        for(int i=count-1;i>=0;i--){
            ui->tableWidget->setItem(select[i],0,nullptr);
            ui->tableWidget->setItem(select[i],1,nullptr);
            ui->tableWidget->setItem(select[i],2,nullptr);
            ui->tableWidget->setItem(select[i],3,nullptr);
            ui->tableWidget->setItem(select[i],4,nullptr);
        }
    }
}

void borrowbook::on_pushButton_5_clicked()
{
    QTableWidgetItem f;
    f.setText("");
    int b=-1;
    QString userID = ui->lineEdit->text();
    if(userID==""){
        QMessageBox::critical(this,"借阅错误","未填写学工号！",QMessageBox::Ok);
    }
    else{
        for(int i=0;i<2;i++){
            if(ui->tableWidget->item(i,1)==nullptr||ui->tableWidget->item(i,1)->text()==f.text())
                continue;
            QTableWidgetItem *c=new QTableWidgetItem();
            c=ui->tableWidget->item(i,1);
            QString ISBN=c->text();
            Librarian lib;
            b=lib.borrowBook(userID,ISBN);//b=借阅书籍函数 的返回值
            if(b==0){
                QMessageBox::critical(this,"借阅错误","不存在该用户",QMessageBox::Ok);
            }else if(b==1){
                QMessageBox::critical(this,"借阅错误","借阅达最大数量！",QMessageBox::Ok);
            }else if(b==3){
                QMessageBox::critical(this,"借阅错误","图书无库存！",QMessageBox::Ok);
            }else if(b==4){
                QMessageBox::information(this,"借阅成功","您已成功借阅选定图书！",QMessageBox::Ok);
            }else{
                QMessageBox::critical(this,"借阅错误","未知错误！",QMessageBox::Ok);
            }
        }
    }
}
