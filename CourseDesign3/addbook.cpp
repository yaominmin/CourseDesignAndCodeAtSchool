#include "addbook.h"
#include "ui_addbook.h"
#include "QSpinBox"
#include "librarian.h"
#include <QTableWidget>
#include <QTableWidgetItem>

addbook::addbook(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addbook)
{
    ui->setupUi(this);
    this->setWindowTitle(tr("添加书籍"));
    this->resize(1200, 500);
    QPalette palette = this->palette();
    palette.setColor(QPalette::Window, QColor(255, 255, 255));
    this->setPalette(palette);
    ui->tableWidget->setFocusPolicy(Qt::NoFocus);    
    ui->tableWidget->verticalHeader()->setDefaultSectionSize(60);
    ui->tableWidget->horizontalHeader()->setDefaultSectionSize(160);
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget->setStyleSheet("selection-background-color:lightblue;");
    ui->tableWidget->horizontalHeader()->setStyleSheet("QHeaderView::section{background:skyblue;}");
    ui->pushButton_2->setToolTip("按住CTRL进行多选");
    QIcon ico_1("://b.png");
    ui->pushButton_2->setIcon(ico_1);
    ui->pushButton_2->setIconSize(QSize(50,50));
    QIcon ico_2("://p.png");
    ui->pushButton->setIcon(ico_2);
    ui->pushButton->setIconSize(QSize(50,40));
    ui->pushButton_2->setStyleSheet("QPushButton{background-color:white;\
                              color: black;   border-radius: 10px;  border: 2px groove gray;\
                              border-style: outset;}"
                              "QPushButton:hover{background-color:black; color: white;}");
    ui->pushButton->setStyleSheet("QPushButton{background-color:white;\
                              color: black;   border-radius: 10px;  border: 2px groove gray;\
                              border-style: outset;}"
                              "QPushButton:hover{background-color:black; color: white;}");
}

addbook::~addbook()
{
    delete ui;
}

//添加图书
void addbook::on_pushButton_clicked()
{
    QTableWidgetItem f;
    f.setText("");
    int b=-1;
    for(int i=0;i<20;i++)
    {
        if(ui->tableWidget->item(i,0)==NULL||ui->tableWidget->item(i,1)==NULL||ui->tableWidget->item(i,0)->text()==f.text()||ui->tableWidget->item(i,1)->text()==f.text())
            continue;
        if(ui->tableWidget->item(i,2)==NULL||ui->tableWidget->item(i,3)==NULL||ui->tableWidget->item(i,2)->text()==f.text()||ui->tableWidget->item(i,3)->text()==f.text())
            continue;
        if(ui->tableWidget->item(i,4)==NULL||ui->tableWidget->item(i,4)->text()==f.text())
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
        QString name=c->text();
        QString ISBN=d->text();
        int num=e->text().toInt();
        QString author=g->text();
        QString publish=h->text();
        QString key=k->text();
        QString intro=l->text();
        Librarian lib;
        b=lib.createBook(ISBN,name,author,publish,intro,key,num,num);
    }
    if(b==-1){
        QMessageBox::critical(this,"添加错误","无完整数据！",QMessageBox::Ok);
    }else if(b==0){
        QMessageBox::information(this,"添加成功","已成功添加有完整信息的书籍！",QMessageBox::Ok);
    }else{
        QMessageBox::information(this,"添加失败","有信息不完整！",QMessageBox::Ok);
    }
//    if(ui->tableWidget->item(0,0) == NULL){
//        QMessageBox::critical(this,"添加错误","必填内容不能为空！",QMessageBox::Ok);
//    }
//    else
//        QMessageBox::information(this,"添加成功","您已成功添加书籍！",QMessageBox::Ok);
}

void addbook::on_pushButton_2_clicked()
{
    bool focus = ui->tableWidget->isItemSelected(ui->tableWidget->currentItem());
    if(!focus){
        QMessageBox::critical(this,"失败提示","请在检索并选择后进行操作！",QMessageBox::Ok);
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
            ui->tableWidget->setItem(select[i],0,NULL);
            ui->tableWidget->setItem(select[i],1,NULL);
            ui->tableWidget->setItem(select[i],2,NULL);
            ui->tableWidget->setItem(select[i],3,NULL);
            ui->tableWidget->setItem(select[i],4,NULL);
            ui->tableWidget->setItem(select[i],5,NULL);
            ui->tableWidget->setItem(select[i],6,NULL);
        }
    }
}
