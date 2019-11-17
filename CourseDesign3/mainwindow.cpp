#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QLabel"
#include "searchbybookname.h"
#include "searchbyauthor.h"
#include "searchbyisbn.h"
#include "searchbypublisher.h"
#include "QCloseEvent"

MainWindow::MainWindow(QWidget *parent)
    :QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle(tr("图书馆借还书系统"));
    this->resize(1250, 700);
    QPalette palette = this->palette();
    palette.setColor(QPalette::Window, QColor(255, 255, 255));
    this->setPalette(palette);
    ui->tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->lineEdit->setPlaceholderText("：请输入");
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);                                //每次选择一行
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);                                 //限制编辑
    ui->tableWidget->setStyleSheet("selection-background-color:lightblue;");                             //选中的背景色
    ui->tableWidget->horizontalHeader()->setStyleSheet("QHeaderView::section{background:skyblue;}");       //设置表头颜色
    ui->tableWidget->clearContents();
    ui->tableWidget->setFocusPolicy(Qt::NoFocus);
    ui->tableWidget->verticalHeader()->setDefaultSectionSize(60);
    ui->tableWidget->horizontalHeader()->setDefaultSectionSize(160);
    QIcon ico("://h.jpg");
    ui->pushButton->setIcon(ico);
    ui->pushButton->setIconSize(QSize(300,100));
    QIcon ico_1("://z.png");
    ui->pushButton_7->setIcon(ico_1);
    ui->pushButton_7->setIconSize(QSize(80,80));
    QIcon ico_2("://x.png");
    ui->pushButton_8->setIcon(ico_2);
    ui->pushButton_8->setIconSize(QSize(80,80));
    QIcon ico_4("://v.png");
    ui->pushButton_5->setIcon(ico_4);
    ui->pushButton_5->setIconSize(QSize(50,50));
    QIcon ico_5("://b.png");
    ui->pushButton_6->setIcon(ico_5);
    ui->pushButton_6->setIconSize(QSize(50,50));
    QIcon ico_6("://image/pictures/hit.PNG");
    ui->pushButton_4->setIcon(ico_6);
    ui->pushButton_4->setIconSize(QSize(280,60));
    QIcon ico_7("://image/pictures/cloud.jpg");
    ui->pushButton_9->setIcon(ico_7);
    ui->pushButton_9->setIconSize(QSize(550,200));
    ui->pushButton_2->setStyleSheet("QPushButton{background-color:white;\
                              color: black;   border-radius: 10px;  border: 2px groove gray;\
                              border-style: outset;}"
                              "QPushButton:hover{background-color:black; color: white;}");
    ui->pushButton_3->setStyleSheet("QPushButton{background-color:white;\
                              color: black;   border-radius: 10px;  border: 2px groove gray;\
                              border-style: outset;}"
                              "QPushButton:hover{background-color:black; color: white;}");
    ui->pushButton_5->setStyleSheet("QPushButton{background-color:white;\
                              color: black;   border-radius: 10px;  border: 2px groove gray;\
                              border-style: outset;}"
                              "QPushButton:hover{background-color:black; color: white;}");
    ui->pushButton_6->setStyleSheet("QPushButton{background-color:white;\
                              color: black;   border-radius: 10px;  border: 2px groove gray;\
                              border-style: outset;}"
                              "QPushButton:hover{background-color:black; color: white;}");
    ui->pushButton_7->setStyleSheet("QPushButton{background-color:white;\
                              color: black;   border-radius: 10px;  border: 2px groove gray;\
                              border-style: outset;}"
                              "QPushButton:hover{background-color:black; color: white;}");
    ui->pushButton_8->setStyleSheet("QPushButton{background-color:white;\
                              color: black;   border-radius: 10px;  border: 2px groove gray;\
                              border-style: outset;}"
                              "QPushButton:hover{background-color:black; color: white;}");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_2_clicked()
{
    bool focus = ui->tableWidget->isItemSelected(ui->tableWidget->currentItem());
    if(!focus){
        QMessageBox::critical(this,"错误提示","请在检索并选择书籍后进行借阅！",QMessageBox::Ok);
    }
    else{
        QStringList* p=new QStringList();
        QList<QTableWidgetSelectionRange>ranges = ui->tableWidget->selectedRanges();
        int count=ranges.count();
        int select[20];
        for(int i=0;i<20;i++)
            select[i]=-1;
        for(int i=0;i<count;i++)
            select[i]=ranges.at(i).topRow();
        int flag=0;
        for(int i=count-1;i>=0;i--){
            QString ISBN=ui->tableWidget->item(select[i],1)->text();
            QString num=ui->tableWidget->item(select[i],4)->text();
            if(num=="0"){
                if(flag==0){
                QMessageBox::critical(this,"错误提示","选择了可借阅书籍数量为0的书籍！",QMessageBox::Ok);
                }
                flag=1;
            }
            else{
            p->append(ISBN);
            }
        }
        if(flag==0){
            borrowbook *dia=new borrowbook();
            connect(this, SIGNAL(sendData(QStringList*)), dia, SLOT(receiveData(QStringList*)));
            emit sendData(p);
            dia->exec();
        }
    }
}


void MainWindow::on_pushButton_3_clicked()
{
    returnbook dia;
    dia.exec();
}

void MainWindow::on_pushButton_7_clicked()
{
    bool focus = ui->tableWidget->isItemSelected(ui->tableWidget->currentItem());
    if(!focus){
        QMessageBox::critical(this,"错误提示","请在检索并选择书籍后进行借阅！",QMessageBox::Ok);
    }
    else{
        QStringList* p=new QStringList();
        QList<QTableWidgetSelectionRange>ranges = ui->tableWidget->selectedRanges();
        int count=ranges.count();
        int select[20];
        for(int i=0;i<20;i++)
            select[i]=-1;
        for(int i=0;i<count;i++)
            select[i]=ranges.at(i).topRow();
        for(int i=count-1;i>=0;i--){
            QString ISBN=ui->tableWidget->item(select[i],1)->text();
            p->append(ISBN);
        }
        borrowbook *dia=new borrowbook();
        connect(this, SIGNAL(sendData(QStringList*)), dia, SLOT(receiveData(QStringList*)));
        emit sendData(p);
        dia->exec();
    }
}

void MainWindow::on_pushButton_8_clicked()
{
    returnbook dia;
    dia.exec();
}

void MainWindow::on_modifyinfo_triggered()
{
    accountinfo dia;
    dia.exec();
}

void MainWindow::on_modifypassword_triggered()
{
    modifypassword dia;
    dia.exec();
}

void MainWindow::on_addreader_triggered()
{
    addreader dia;
    dia.exec();
}

void MainWindow::on_managereaders_triggered()
{
    managereaders dia;
    dia.exec();
}

void MainWindow::on_addbook_triggered()
{
    addbook dia;
    dia.exec();
}

void MainWindow::on_managebooks_triggered()
{
    managebooks dia;
    dia.exec();
}


void MainWindow::on_help_triggered()
{
    helptxt dia;
    dia.exec();
}

void MainWindow::on_about_triggered()
{
    abouttxt dia;
    dia.exec();
}

void MainWindow::on_pushButton_6_clicked()
{
    ui->tableWidget->clearContents();
}

void MainWindow::on_pushButton_5_clicked()
{
    QString a;
    int b=0;
    int c=0;
    int row=-1;
    Book * book[100];
    for(int i=0;i<100;i++)
    {
        book[i]=new Book();
    }
    a = ui->lineEdit->text();
    b = ui->comboBox->currentIndex();
    SearchByBookName bybook;
    SearchByISBN byISBN;
    SearchByAuthor byauthor;
    SearchByPublisher bypublish;
    switch (b){
    case 0:
        c = bybook.search(a,book,row);
        break;
    case 1:
        c = byISBN.search(a,book);
        row=c;
        break;
    case 2:
        c = byauthor.search(a,book,row);
        break;
    case 3:
        c = bypublish.search(a,book,row);
        break;
    }
    if(c==0){
        QMessageBox::information(this,"查找失败","未查询到相关书籍！",QMessageBox::Ok);
    }
    if(row==0){
        QMessageBox::information(this,"查找失败","未查询到相关书籍！",QMessageBox::Ok);
    }
    ui->tableWidget->setRowCount(row);
    for(int i=0;i<row;i++)
    {
        //if(book[i]->getISBN()!=""||book[i]->getISBN()!=nullptr){
            ui->tableWidget->setItem(i,0,new QTableWidgetItem(book[i]->getBookName()));
            ui->tableWidget->setItem(i,1,new QTableWidgetItem(book[i]->getISBN()));
            ui->tableWidget->setItem(i,2,new QTableWidgetItem(book[i]->getAuthor()));
            ui->tableWidget->setItem(i,3,new QTableWidgetItem(book[i]->getPublisher()));
            QString str="";
            str=QString::number(book[i]->getAvailable());
            if(str == nullptr){
                break;
            }
            ui->tableWidget->setItem(i,4,new QTableWidgetItem(str));
            ui->tableWidget->setItem(i,5,new QTableWidgetItem(book[i]->getKeyword()));
            ui->tableWidget->setItem(i,6,new QTableWidgetItem(book[i]->getIntroduction()));
      //  }
    }
    ui->tableWidget->resizeColumnsToContents();
}

void MainWindow::closeEvent(QCloseEvent *event) //系统自带退出确定程序
{
    int choose;
    choose= QMessageBox::question(this, tr("退出程序"),
                                   QString(tr("确认退出程序?")),
                                   QMessageBox::Yes | QMessageBox::No);

    if (choose== QMessageBox::No)
     {
          event->ignore();  //忽略//程序继续运行
    }
    else if (choose== QMessageBox::Yes)
    {
          event->accept();  //介绍//程序退出
    }
}
