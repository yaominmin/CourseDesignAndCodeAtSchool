#include "returnbook.h"
#include "ui_returnbook.h"
#include "QScrollBar"
#include "QSlider"
#include "QAbstractScrollArea"
#include "librarian.h"
#include "QMessageBox"
#include "dboperation.h"

returnbook::returnbook(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::returnbook)
{
    ui->setupUi(this);
    this->setWindowTitle(tr("归还书籍"));
    this->resize(1200, 700);
    QPalette palette = this->palette();
    palette.setColor(QPalette::Window, QColor(255, 255, 255));
    this->setPalette(palette);
    ui->tableWidget->setShowGrid(true);                                                                  //显示边框
    ui->tableWidget->setFocusPolicy(Qt::NoFocus);
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);                                 //限制编辑
    ui->tableWidget->setStyleSheet("selection-background-color:lightblue;");                               //多选，即shift，ctrl常规操作
    ui->tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->lineEdit->setPlaceholderText("：输入信息进行检索");
    ui->tableWidget->verticalHeader()->setDefaultSectionSize(60);
    ui->tableWidget->horizontalHeader()->setStyleSheet("QHeaderView::section{background:skyblue;}");
    QIcon ico_6("://image/pictures/hit.PNG");
    ui->pushButton_4->setIcon(ico_6);
    ui->pushButton_4->setIconSize(QSize(400,100));
    QIcon ico_4("://v.png");
    ui->pushButton_3->setIcon(ico_4);
    ui->pushButton_3->setIconSize(QSize(50,50));
    QIcon ico_2("://z.png");
    ui->pushButton_2->setIcon(ico_2);
    ui->pushButton_2->setIconSize(QSize(50,50));
    QIcon ico_5("://x.png");
    ui->pushButton_5->setIcon(ico_5);
    ui->pushButton_5->setIconSize(QSize(50,50));
//    ui->tableWidget->verticalScrollBar()->setStyleSheet(                                                   //竖滚动条美化
//            "QScrollBar:vertical{"
//            "background:skyblue;"
//            "padding-top:30px;"
//            "padding-bottom:30px;"
//            "padding-left:1px;"
//            "padding-right:2px;"
//            "border-left:1px solid skyblue;}"
//            "QScrollBar{"
//            "background:transparent;"
//            "width: 20px;}"
//            "QScrollBar::handle{"
//            "background:blue;"
//            "min-height:40px;"
//            "border:0px solid transparent;"
//            "border-radius:1px;}"
//            "QScollBar::add-page:vertical, QScrollBar::sub-page:vertical{background:skyblue;}"
//            "QScollBar::add-line:vertical, QScrollBar::sub-line:vertical{background:skyblue;}"
//            "QScrollBar::handle:hover{background:green;}"
//            "QScrollBar::sub-line{background:transparent;}"
//            "QScrollBar::add-line{background:transparent;}");
//    ui->tableWidget->horizontalScrollBar()->setStyleSheet(                                                     //横滚动条美化
//            "QScrollBar:horizontal{"
//            "background:skyblue;"
//            "padding-top:1px;"
//            "padding-bottom:1px;"
//            "padding-left:30px;"
//            "padding-right:30px;"
//            "border-left:1px solid skyblue;}"
//            "QScrollBar{"
//            "background:transparent;"
//            "height: 20px;}"
//            "QScrollBar::handle{"
//            "background:blue;"
//            "min-height:40px;"
//            "border:0px solid transparent;"
//            "border-radius:1px;}"
//            "QScollBar::add-page:horizontal, QScrollBar::sub-page:horizontal{background:skyblue;}"
//            "QScollBar::add-line:horizontal, QScrollBar::sub-line:horizontal{background:skyblue;}"
//            "QScrollBar::handle:hover{background:green;}"
//            "QScrollBar::sub-line{background:transparent;}"
//            "QScrollBar::add-line{background:transparent;}");
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
}

returnbook::~returnbook()
{
    delete ui;
}

//查找按钮
void returnbook::on_pushButton_3_clicked()
{
    int row=-1;
    BookOperation * bookOperation[100];
    for(int i=0;i<100;i++)
    {
        bookOperation[i]=new BookOperation();
    }
    Book * book[100];
    for(int i=0;i<100;i++)
    {
        book[i]=new Book();
    }
    Reader * reader[100];
    for(int i=0;i<100;i++)
    {
        reader[i]=new Reader();
    }
    QString userID = ui->lineEdit->text();
    Librarian *lib = new Librarian();
    //row=搜素到的符合的结果个数
    row = lib->searchRBL(userID,bookOperation,book,reader);
    ui->tableWidget->setRowCount(row);
    for(int i=0;i<row;i++)
    {
        ui->tableWidget->setItem(i,0,new QTableWidgetItem(reader[i]->getUserID()));
        ui->tableWidget->setItem(i,1,new QTableWidgetItem(reader[i]->getName()));
        ui->tableWidget->setItem(i,2,new QTableWidgetItem(bookOperation[i]->getISBN()));
        ui->tableWidget->setItem(i,3,new QTableWidgetItem(book[i]->getBookName()));

        ui->tableWidget->setItem(i,4,new QTableWidgetItem(book[i]->getAuthor()));
        ui->tableWidget->setItem(i,5,new QTableWidgetItem(book[i]->getPublisher()));
        ui->tableWidget->setItem(i,6,new QTableWidgetItem(bookOperation[i]->getstate()));
        QString str;
        str = bookOperation[i]->getreturnDate().addMonths(-1).toString("yyyy.MM.dd");
        ui->tableWidget->setItem(i,7,new QTableWidgetItem(str));
        str = bookOperation[i]->getreturnDate().toString("yyyy.MM.dd");
        ui->tableWidget->setItem(i,8,new QTableWidgetItem(str));
        if(row==0){
            QMessageBox::critical(this,"查询失败","无借阅记录！",QMessageBox::Ok);
        }
    }
    ui->tableWidget->resizeColumnsToContents();
}

void returnbook::on_pushButton_5_clicked()
{
    QString userID = ui->lineEdit->text();
    if(userID==""||userID==nullptr){
        QMessageBox::critical(this,"失败提示","请先输入学工号进行查询！",QMessageBox::Ok);
        return;
    }
    bool focus = ui->tableWidget->isItemSelected(ui->tableWidget->currentItem());
    if(!focus){
        QMessageBox::critical(this,"错误提示","请在检索并选择书籍后进行操作！",QMessageBox::Ok);
        return;
    }
    QList<QTableWidgetSelectionRange>ranges = ui->tableWidget->selectedRanges();
    int count=ranges.count();
    int select[20];
    int flag=-1;
    for(int i=0;i<20;i++)
        select[i]=-1;
    for(int i=0;i<count;i++)
        select[i]=ranges.at(i).topRow();
    for(int i=count-1;i>=0;i--){
        QTableWidgetItem *ISBN=new QTableWidgetItem();
        ISBN=ui->tableWidget->item(select[i],2);
        Librarian lib;
        flag=lib.returnBook(userID,ISBN->text());
    }
    //0 无此ID,1 无此借阅记录, 2 成功还书
    if(flag==0){
        QMessageBox::critical(this,"还书失败","无此读者学工号！",QMessageBox::Ok);
    }else if(flag==1){
        QMessageBox::critical(this,"还书失败","无此借阅记录或书籍已归还！",QMessageBox::Ok);
    }else if(flag==2){
        QMessageBox::information(this,"还书成功","书籍已归还！",QMessageBox::Ok);
        on_pushButton_3_clicked();
    }else{
        QMessageBox::critical(this,"还书失败","未知错误！",QMessageBox::Ok);
    }
}

//续借按钮
void returnbook::on_pushButton_2_clicked()
{
    QString userID = ui->lineEdit->text();
    if(userID == nullptr){
        QMessageBox::critical(this,"错误","未填写学工号！",QMessageBox::Ok);
    }
    else{
        QList<QTableWidgetSelectionRange>ranges = ui->tableWidget->selectedRanges();
        if(ranges.empty()){
            QMessageBox::critical(this,"错误","请在检索并选择书籍后进行操作！！",QMessageBox::Ok);
        }
        else{
            int flag=-1;
            int s = ranges.at(0).topRow();
            QTableWidgetItem *ISBN=new QTableWidgetItem();
            ISBN=ui->tableWidget->item(s,2);
            Librarian lib;
            //为读者续借//0 无此ID,1 无此借阅记录,2成功续借 3图书状态为已归还
            if(ui->tableWidget->item(s,6)->text()=="归还"){
                QMessageBox::critical(this,"续借失败","该书已归还！",QMessageBox::Ok);
            }
            else{
            flag=lib.continueBorrow(userID,ISBN->text());
            if(flag==0){
                QMessageBox::critical(this,"续借失败","无此读者学工号！",QMessageBox::Ok);
            }
            else if(flag==2){
                QMessageBox::information(this,"续借成功","未归还的书籍已续借！",QMessageBox::Ok);
            }
            else{
                QMessageBox::critical(this,"续借失败","未知错误！",QMessageBox::Ok);
            }
            }
        }
    }
}
