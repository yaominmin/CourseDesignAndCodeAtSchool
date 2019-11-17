#include "managebooks.h"
#include "ui_managebooks.h"
#include "searchbyauthor.h"
#include "searchbybookname.h"
#include "searchbyisbn.h"
#include "searchbypublisher.h"
#include "librarian.h"

managebooks::managebooks(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::managebooks)
{
    ui->setupUi(this);
    this->setWindowTitle(tr("管理书籍"));
    this->resize(1400, 500);
    QPalette palette = this->palette();
    palette.setColor(QPalette::Window, QColor(255, 255, 255));
    this->setPalette(palette);
    ui->tableWidget->setFocusPolicy(Qt::NoFocus);
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget->setStyleSheet("selection-background-color:lightblue;");    
    ui->tableWidget->verticalHeader()->setDefaultSectionSize(60);
    ui->tableWidget->horizontalHeader()->setDefaultSectionSize(160);
    ui->tableWidget->horizontalHeader()->setStyleSheet("QHeaderView::section{background:skyblue;}");
    ui->pushButton->setToolTip("按住CTRL进行多选");
    ui->lineEdit->setPlaceholderText("：输入信息进行检索");
    QIcon ico("://v.png");
    ui->pushButton_5->setIcon(ico);
    ui->pushButton_5->setIconSize(QSize(50,50));
    QIcon ico_1("://b.png");
    ui->pushButton->setIcon(ico_1);
    ui->pushButton->setIconSize(QSize(50,50));
    QIcon ico_2("://p.png");
    ui->pushButton_6->setIcon(ico_2);
    ui->pushButton_6->setIconSize(QSize(50,40));    
    QIcon ico_4("://v.png");
    ui->pushButton_5->setIcon(ico_4);
    ui->pushButton_5->setIconSize(QSize(50,50));
    QIcon ico_6("://image/pictures/hit.PNG");
    ui->pushButton_4->setIcon(ico_6);
    ui->pushButton_4->setIconSize(QSize(280,60));
    ui->pushButton->setStyleSheet("QPushButton{background-color:white;\
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
}

managebooks::~managebooks()
{
    delete ui;
}
//删除所选
void managebooks::on_pushButton_clicked()
{
    bool focus = ui->tableWidget->isItemSelected(ui->tableWidget->currentItem());
    if(!focus){
        QMessageBox::critical(this,"失败提示","请在检索并选中书籍后进行操作！",QMessageBox::Ok);
    }
    else{
        bool focus = ui->tableWidget->isItemSelected(ui->tableWidget->currentItem());
        if(!focus){
            QMessageBox::critical(this,"失败提示","请在检索并选中读者后进行操作！",QMessageBox::Ok);
        }
        else{
            QMessageBox messageBox(QMessageBox::NoIcon,
                                      "删除", "你确定要删除吗?",
                                      QMessageBox::Yes | QMessageBox::No, NULL); ;
               int result=messageBox.exec();
               switch (result)
               {
               case QMessageBox::Yes:{
                   QList<QTableWidgetSelectionRange>ranges = ui->tableWidget->selectedRanges();
                   int count=ranges.count();
                   int select[20];
                   for(int i=0;i<20;i++)
                       select[i]=-1;
                   for(int i=0;i<count;i++)
                       select[i]=ranges.at(i).topRow();
                   for(int i=count-1;i>=0;i--){
                       QTableWidgetItem *ISBN=new QTableWidgetItem();
                       ISBN=ui->tableWidget->item(select[i],1);
                       Librarian lib;
                       lib.deleBookInfo(ISBN->text());
                   }
                   for(int i=count-1;i>=0;i--){
                       ui->tableWidget->setItem(select[i],0,NULL);
                       ui->tableWidget->setItem(select[i],1,NULL);
                       ui->tableWidget->setItem(select[i],2,NULL);
                       ui->tableWidget->setItem(select[i],3,NULL);
                       ui->tableWidget->setItem(select[i],4,NULL);
                       ui->tableWidget->setItem(select[i],5,NULL);
                       ui->tableWidget->setItem(select[i],6,NULL);
                   }
                   break;
                   }
               case QMessageBox::No:
                   break;
               default:
                   break;
               }
           }
    }
}
//批量修改书籍信息
void managebooks::on_pushButton_6_clicked()
{
    bool focus = ui->tableWidget->isItemSelected(ui->tableWidget->currentItem());
    if(!focus){
        QMessageBox::critical(this,"失败提示","请在检索并修改后进行操作！",QMessageBox::Ok);
    }
    else{
        QTableWidgetItem f;
        f.setText("");
        int b=-1;
        for(int i=0;i<20;i++)
        {
            if(ui->tableWidget->item(i,0)==NULL||ui->tableWidget->item(i,1)==NULL||ui->tableWidget->item(i,0)->text()==f.text()||ui->tableWidget->item(i,1)->text()==f.text())
                continue;
            if(ui->tableWidget->item(i,2)==NULL||ui->tableWidget->item(i,3)==NULL||ui->tableWidget->item(i,2)->text()==f.text()||ui->tableWidget->item(i,3)->text()==f.text())
                continue;
            if(ui->tableWidget->item(i,4)==NULL||ui->tableWidget->item(i,5)==NULL||ui->tableWidget->item(i,4)->text()==f.text()||ui->tableWidget->item(i,5)->text()==f.text())
                continue;
            QTableWidgetItem *c=new QTableWidgetItem();
            c=ui->tableWidget->item(i,0);
            QTableWidgetItem *d=new QTableWidgetItem();
            d=ui->tableWidget->item(i,1);
            QTableWidgetItem *e=new QTableWidgetItem();
            e=ui->tableWidget->item(i,2);
            QTableWidgetItem *g=new QTableWidgetItem();
            g=ui->tableWidget->item(i,3);
            QTableWidgetItem *h=new QTableWidgetItem();
            h=ui->tableWidget->item(i,4);
            QTableWidgetItem *k=new QTableWidgetItem();
            k=ui->tableWidget->item(i,5);
            QTableWidgetItem *l=new QTableWidgetItem();
            l=ui->tableWidget->item(i,6);
            QTableWidgetItem *m=new QTableWidgetItem();
            m=ui->tableWidget->item(i,7);
            QString name=c->text();
            QString ISBN=d->text();
            QString author=e->text();
            QString publish=g->text();
            int gcnum=h->text().toInt();
            int kjnum=k->text().toInt();
            QString key="";
            key=l->text();
            QString intro="";
            intro=m->text();
            Librarian *library=new Librarian();
            b=library->changeBookInfo(ISBN,name,author,publish,intro,key,gcnum,kjnum);
        }
        QMessageBox::information(this,"更改成功","已保存修改后完整的书籍信息！",QMessageBox::Ok);
    }
}

void managebooks::on_pushButton_5_clicked()
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
        QMessageBox::critical(this,"查找失败","未查询到相关书籍！",QMessageBox::Ok);
    }
    if(row==0){
        QMessageBox::critical(this,"查找失败","未查询到相关书籍！",QMessageBox::Ok);
    }
    for(int i=0;i<row;i++)
    {
        ui->tableWidget->setItem(i,0,new QTableWidgetItem(book[i]->getBookName()));
        ui->tableWidget->setItem(i,1,new QTableWidgetItem(book[i]->getISBN()));
        ui->tableWidget->setItem(i,2,new QTableWidgetItem(book[i]->getAuthor()));
        ui->tableWidget->setItem(i,3,new QTableWidgetItem(book[i]->getPublisher()));
        QString bb;
        bb=QString::number(book[i]->getCollectionNum());
        ui->tableWidget->setItem(i,4,new QTableWidgetItem(bb));
        QString aa;
        aa=QString::number(book[i]->getAvailable());
        ui->tableWidget->setItem(i,5,new QTableWidgetItem(aa));
        ui->tableWidget->setItem(i,6,new QTableWidgetItem(book[i]->getKeyword()));
        ui->tableWidget->setItem(i,7,new QTableWidgetItem(book[i]->getIntroduction()));
    }
    ui->tableWidget->resizeColumnsToContents();
}
